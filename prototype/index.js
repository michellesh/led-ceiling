const SVG_WIDTH = 700;
const SVG_HEIGHT = 700;
const RADIUS = SVG_WIDTH / 2;

const colorScale = d3.scaleLinear().domain([0, 10]).range(['#ffffff', '#0000ff'])

const random = (small = 0, big = 10) =>
  small + Math.floor(Math.random() * (big - small));

const distance = (x1, y1, x2, y2) =>
  Math.sqrt(Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2));

const ledGrid = ({ cushion = 10, ledRadius = 1 } = {}) => {
  let leds = [];
  let ledCount = 0;

  const svg = d3.select('body').append('svg')
      .attr('width', SVG_WIDTH)
      .attr('height', SVG_HEIGHT);

  const circle = (x, y, r, color) => {
    return svg.append('circle')
      .attr('fill', color || colorScale(random()))
      .attr('cx', x)
      .attr('cy', y)
      .attr('r', r);
  };

  xs = d3.range(0, SVG_WIDTH + cushion, cushion);
  ys = d3.range(0, SVG_HEIGHT + cushion, cushion);

  xs.forEach((x, row) => {
    leds.push([]);
    ys.forEach((y, col) => {
      if (distance(x, y, RADIUS, RADIUS) < RADIUS) {
        leds[row].push({ x, y, circle: circle(x, y, ledRadius, 'blue') });
        ledCount++;
      }
    });
  });

  leds = leds.filter(row => row.length > 0);

  console.log('ledCount',ledCount);
  console.log('leds',leds);

  return leds;
};
