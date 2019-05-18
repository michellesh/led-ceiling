const cushion = 10;
const ledRadius = 1;
const rippleWidth = 50;
const leds = ledGrid({ cushion, ledRadius });

const increaseRadius = d3.scaleLinear().domain([0, rippleWidth]).range([2, 5]);
const decreaseRadius = d3.scaleLinear().domain([0, rippleWidth]).range([5, 2]);
const increaseColor = d3.scaleLinear().domain([0, rippleWidth]).range(['blue', 'white']);
const decreaseColor = d3.scaleLinear().domain([0, rippleWidth]).range(['white', 'blue']);

const donut = (x, y, r) => {
  leds.forEach(row => {
    row.forEach(p => {
      d = distance(p.x, p.y, x, y);
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

const ripple = (x, y) => {
  let r = 0;
  let interval = setInterval(() => {
    if (r > RADIUS * 2) {
      clearInterval(interval);
    }
    r += 10;
    donut(x, y, r);
  }, 100)
};

ripple(400, 250);
