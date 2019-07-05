const cushion = 20;
const ledRadius = 1;
const leds = ledGrid({ cushion, ledRadius });

const TENSION = 55.0; // the tension in the strings
const SPACING = 10.0; // the distance between masses on the string
const MASS = 0.005; // the mass of each pixel
const MAX_POSITION = SPACING/100.0;
const MIN_POSITION = -SPACING/100.0;
const GAMMA = .0185; // the damping constant (without this the waves will reflect off the free end and continue forever)
const NUM_COLORS = 1000; // the number of shades of blue
const TSTEP = .0015;

colorScale = d3.scaleLinear()
  .domain([0, NUM_COLORS])
  .range(['#0000ff', '#ffffff']);

random = (small = 0, big = 10) => small + Math.random() * (big - small);

const avg = arr => arr.reduce((acc, n) => acc + n, 0) / arr.length;

const map = (x, inMin, inMax, outMin, outMax) =>
  ((x - inMin) / (inMax - inMin)) * (outMax - outMin) + outMin;

let damping, force, colorIndex, brightnesses = [];

const waterRandom = () => {
  leds.forEach((strand, row) => {
    strand.forEach((p, col) => {
      const n = random(0, NUM_COLORS);
      p.circle.attr('fill', colorScale(n));
      p.circle.attr('r', n / NUM_COLORS * 2.5);
    });
  });
};

// start with random positions
const init = () => {
  leds.forEach((strand, row) => {
    strand.forEach((p, col) => {
      p.position = random(MIN_POSITION, MAX_POSITION);
    });
  });
};

const water = time => {
  leds.forEach((strand, row) => {
    strand.forEach((p, col) => {
      // calculate the force on this point based on its and its neighbors positions
      let positionTerm = 0;

      // above
      if (leds[row-1] && leds[row-1][col]) {
        positionTerm += p.position - leds[row-1][col].position;
      }
      // below
      if (leds[row+1] && leds[row+1][col]) {
        positionTerm += p.position - leds[row+1][col].position;
      }
      // left
      if (leds[row][col-1]) {
        positionTerm += p.position - leds[row][col-1].position;
      }
      // right
      if (leds[row][col+1]) {
        positionTerm += p.position - leds[row][col+1].position;
      }

      p.position = p.position > MAX_POSITION ? MAX_POSITION : p.position;
      p.position = p.position < MIN_POSITION ? MIN_POSITION : p.position;

      // calculate the force as the sum of the z-component of the tensions minus the damping
      damping = GAMMA * p.velocity;
      // TODO why TENSION/SPACING?
      force = -(TENSION/SPACING) * positionTerm - damping;

      // update the position and velocity
      // TODO look up Taylor Expansions?
      p.position = p.position + (p.velocity * TSTEP) + 0.5 * (force / MASS) * TSTEP * TSTEP;
      p.velocity = p.velocity + (force / MASS) * TSTEP;

      // assign color to the pixel according to the position and velocity
      colorIndex = map(p.position, MIN_POSITION, MAX_POSITION, 0, NUM_COLORS);
      p.color = colorScale(colorIndex);

      // take the absolute value of value in range -0.1 < x < 0.1
      // the closer the value to is to actual blue, the brighter, and same for white
      p.brightness = map(Math.abs(p.position), 0, MAX_POSITION, 0, NUM_COLORS) / NUM_COLORS;
      brightnesses.push(p.brightness);

      p.circle.attr('fill', p.color);
      p.circle.attr('r', p.brightness * 2.5);
    });
  });
}

init();
let time = 0;
const intervalId = setInterval(() => {
  brightnesses = [];
  if (time === 0) {
    //clearInterval(intervalId);
  }
  water(time);
  //waterRandom();

  //console.log('average brightness', avg(brightnesses) * 100);

  time++;
},100);
