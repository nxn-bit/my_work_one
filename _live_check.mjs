// temporary probe: check the LIVE GitHub Pages site
const BASE = 'https://nxn-bit.github.io/my_work_one/';
const FILES = [
  '',
  'index.html',
  'xiao-0408-work1.html',
  'style.css',
  'script.js',
  'assets/hero-1.jpg',
  'assets/hero-2.jpg',
  'assets/hero-3.jpg',
  'assets/film-still.jpg',
  'assets/mini.jpg',
  'assets/grid-1.jpg',
  'assets/grid-2.jpg',
  'assets/grid-3.jpg',
  'assets/mid.jpg',
  'assets/favicon.svg',
];

console.log('文件 / 路径'.padEnd(30) + '状态'.padEnd(10) + '大小'.padEnd(12) + 'content-type');
console.log('-'.repeat(80));

let missing = [];
let okCount = 0;

for (const f of FILES) {
  const url = BASE + f;
  try {
    const res = await fetch(url, { redirect: 'follow' });
    const buf = Buffer.from(await res.arrayBuffer());
    const label = f === '' ? '(根目录)' : f;
    console.log(
      label.padEnd(30) +
      String(res.status).padEnd(10) +
      ((buf.length / 1024).toFixed(1) + ' KB').padEnd(12) +
      (res.headers.get('content-type') || '-')
    );
    if (res.ok) okCount++; else missing.push(`${res.status} ${label}`);
  } catch (e) {
    console.log((f === '' ? '(根目录)' : f).padEnd(30) + 'ERR       ' + e.message);
    missing.push('ERR ' + f);
  }
}

console.log(`\n成功 ${okCount} / ${FILES.length}`);
if (missing.length) {
  console.log('\n===== 缺失或异常 =====');
  missing.forEach(m => console.log('  ✗ ' + m));
} else {
  console.log('\n全部资源正常 ✓');
}

/* 检查首页实际引用，看是否指向存在的文件 */
console.log('\n===== xiao-0408-work1.html 引用的资源在线上是否存在 =====');
try {
  const html = await (await fetch(BASE + 'xiao-0408-work1.html')).text();
  const refs = new Set();
  for (const m of html.matchAll(/(?:src|href)="([^"]+)"/g)) {
    if (!/^https?:\/\//.test(m[1]) && m[1] !== '#') refs.add(m[1]);
  }
  for (const m of html.matchAll(/url\('([^']+)'\)/g)) refs.add(m[1]);
  for (const r of [...refs].sort()) {
    const res = await fetch(BASE + r, { method: 'GET' });
    console.log(`  ${res.ok ? '✓' : '✗'} ${String(res.status).padEnd(5)} ${r}`);
  }
} catch (e) {
  console.log('  失败: ' + e.message);
}

/* 首页是否是 index.html */
console.log('\n===== 根目录返回的是什么 =====');
try {
  const r = await fetch(BASE);
  const t = await r.text();
  console.log('  标题:', (t.match(/<title>([^<]*)<\/title>/i) || [])[1] || '(无)');
  console.log('  含 CINEMA DIARY:', t.includes('CINEMA DIARY') ? '是' : '否');
  console.log('  含 My first page:', t.includes('My first page') ? '是' : '否');
} catch (e) {
  console.log('  失败: ' + e.message);
}
