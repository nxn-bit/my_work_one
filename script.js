document.addEventListener('DOMContentLoaded', () => {

    /* ==========================================================
       1. 首屏轮播图（每 4 秒切换一次）
       ========================================================== */
    const slides = document.querySelectorAll('.slide');
    let currentSlide = 0;
    const slideInterval = 4000;

    function nextSlide() {
        if (!slides.length) return;
        slides[currentSlide].classList.remove('active');
        currentSlide = (currentSlide + 1) % slides.length;
        slides[currentSlide].classList.add('active');
    }

    setInterval(nextSlide, slideInterval);

    /* ==========================================================
       2. 轮播图自动换真图
          真图路径: assets/hero-1.jpg、hero-2.jpg、hero-3.jpg
          文件不存在 -> 自动保留 assets/hero-N.svg 占位图
       ========================================================== */

    function imageExists(url) {
        // 不缓存结果，这样你把真图放进 assets/ 后刷新页面就能立刻生效
        return new Promise(resolve => {
            const probe = new Image();
            probe.onload = () => resolve(true);
            probe.onerror = () => resolve(false);
            probe.src = url;
        });
    }

    function upgradeSlides() {
        slides.forEach(slide => {
            const real = slide.dataset.bg;
            if (!real) return;
            const placeholder = real.replace(/\.(jpe?g|png|webp)$/i, '.svg');

            imageExists(real).then(exists => {
                if (!exists) {
                    // 真图还没加进来，保持占位图
                    if (!slide.style.backgroundImage || slide.style.backgroundImage === 'none') {
                        slide.style.backgroundImage = `url('${placeholder}')`;
                    }
                    return;
                }
                if (slide.classList.contains('active')) {
                    slide.style.backgroundImage = `url('${real}')`;
                } else {
                    // 预先加载好，轮到这张时才不会闪白
                    const pre = new Image();
                    pre.onload = () => { slide.style.backgroundImage = `url('${real}')`; };
                    pre.src = real;
                }
            });
        });
    }

    upgradeSlides();
    // 加载完成后再查一次，避免首次探测太早
    window.addEventListener('load', upgradeSlides);
});
