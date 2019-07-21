const SVG_WIDTH = 700;
const SVG_HEIGHT = 700;
const RADIUS = SVG_WIDTH / 2;
const LED_COLOR = 'white';
const h = (Math.sqrt(3)/2);

let colorScale = d3.scaleLinear().domain([0, 10]).range(['#ffffff', '#0000ff'])

let random = (small = 0, big = 10) =>
  small + Math.floor(Math.random() * (big - small));

const distance = (x1, y1, x2, y2) =>
  Math.sqrt(Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2));

const isInsideHexagon = (x, y, vertices) => {
  const areaOfTriangle = (x1, y1, x2, y2, x3, y3) => {
    return Math.abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
  }
  let a, a1, a2, a3, sum;
  const isInsideTriangle = (x1, y1, x2, y2, x3, y3, x, y) => {
    a =  areaOfTriangle(x1, y1, x2, y2, x3, y3);
    a1 = areaOfTriangle(x, y, x2, y2, x3, y3);
    a2 = areaOfTriangle(x1, y1, x, y, x3, y3);
    a3 = areaOfTriangle(x1, y1, x2, y2, x, y);
    sum = a1 + a2 + a3;
    return a >= sum - 1 && a <= sum + 1;
  }
  return vertices.some((p1, i) => {
    const p2 = vertices[i + 1] || vertices[0];
    return isInsideTriangle(RADIUS, RADIUS, p1.x, p1.y, p2.x, p2.y, x, y);
  });
};

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

const ledGrid = ({
  cushion = 22, // the space between each LED
  ledRadius = 1,
  showOutline = false,
} = {}) => {

  let leds = [];
  let ledCount = 0;

  const vertices = [
    { x: RADIUS + RADIUS, y: RADIUS},
    { x: RADIUS/2 + RADIUS, y: RADIUS*h + RADIUS},
    { x: -RADIUS/2 + RADIUS, y: RADIUS*h + RADIUS},
    { x: -RADIUS + RADIUS, y: RADIUS},
    { x: -RADIUS/2 + RADIUS, y: -RADIUS*h + RADIUS},
    { x: RADIUS/2 + RADIUS, y: -RADIUS*h + RADIUS}
  ];

  if (showOutline) {
    svg.append('path')
      .attr('d', vertices.map((p, i) => [(i === 0 ? 'M' : 'L'), p.x, p.y].join(' ')).join(' ') + ' Z')
      .attr('stroke-width', 1)
      .attr('stroke', LED_COLOR)
  }

  xs = d3.range(0, SVG_WIDTH + cushion, cushion);
  ys = d3.range(0, SVG_HEIGHT + cushion, cushion);

  ys.forEach((y, col) => {
    leds.push([]);
    xs.forEach((x, row) => {
      if (isInsideHexagon(x, y, vertices)) {
        leds[col].push({
          circle: circle(x, y, ledRadius, LED_COLOR),
          color: LED_COLOR,
          col,
          row,
          position: 0,
          velocity: 0,
          x,
          y,
        });
        ledCount++;
      }
    });
  });

  leds = leds.filter(row => row.length > 0);

  console.log('ledCount',ledCount);
  console.log('leds',leds);

  return leds;
};

const ledCircleGrid = ({ cushion = 10, ledRadius = 1 } = {}) => {
  let leds = [];
  let ledCount = 0;

  xs = d3.range(0, SVG_WIDTH + cushion, cushion);
  ys = d3.range(0, SVG_HEIGHT + cushion, cushion);

  ys.forEach((y, col) => {
    leds.push([]);
    xs.forEach((x, row) => {
      if (distance(x, y, RADIUS, RADIUS) < RADIUS) {
        leds[col].push({
          circle: circle(x, y, ledRadius, LED_COLOR),
          color: LED_COLOR,
          col,
          row,
          position: 0,
          velocity: 0,
          x,
          y,
        });
        ledCount++;
      }
    });
  });

  leds = leds.filter(row => row.length > 0);

  console.log('ledCount',ledCount);
  console.log('leds',leds);

  return leds;
};
