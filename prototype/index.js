let random = (small = 0, big = 10) =>
  small + Math.floor(Math.random() * (big - small));

const ledRadius = 1;
const cushion = 22;
const leds = ledGrid({ cushion, ledRadius });

water(leds);
