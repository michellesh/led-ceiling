const rippleWidth = 50;

const increaseRadius = d3.scaleLinear().domain([0, rippleWidth]).range([2, 5]);
const decreaseRadius = d3.scaleLinear().domain([0, rippleWidth]).range([5, 2]);
const increaseColor = d3.scaleLinear().domain([0, rippleWidth]).range(['blue', 'white']);
const decreaseColor = d3.scaleLinear().domain([0, rippleWidth]).range(['white', 'blue']);

const donut = (leds, x, y, r) => {
  leds.forEach(row => {
    row.forEach(p => {
      d = distance(p.x, p.y, x, y);
      // stop drawing the circle once it gets pretty big
      if (d > RADIUS * 1.5) {
        return;
      }
      // The point is inside the circle if the distance from it to the center is at most r
      if (d < r && d > (r - rippleWidth)) {
        const prominence = r - d;
        if ((prominence - (rippleWidth / 2)) < 0) {
          p.circle.attr('r', increaseRadius(prominence));
          p.circle.attr('fill', increaseColor(prominence));
        } else {
          p.circle.attr('r', decreaseRadius(prominence));
          p.circle.attr('fill', decreaseColor(prominence));
        }
      } else if (d < (r - rippleWidth)) {
        p.circle.attr('r', ledRadius);
        p.circle.attr('fill', 'blue');
      }
    });
  });
};

const ripple = (leds, count = 10) => {
  for (let i = 0, p = Promise.resolve(); i < count; i++) {
    p = p.then(() => new Promise(resolve =>{
      const randomY = random(0, leds.length);
      const randomX = random(0, leds[randomY].length);
      const point = leds[randomY][randomX];

      let r = 0;
      let interval = setInterval(() => {
        if (r > RADIUS * 2) {
          clearInterval(interval);
          resolve();
        }
        r += 10;
        donut(leds, point.x, point.y, r);
      }, 100);
    }));
  }
};
