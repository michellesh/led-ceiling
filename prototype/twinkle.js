const cushion = 10;
const ledRadius = 1;
const leds = ledGrid({ cushion, ledRadius });

const twinkle = () => {
  setInterval(() => {
    leds.forEach(row => {
      row.forEach(p => {
        p.circle.attr('fill', colorScale(random()));
      });
    });
  }, 100);
};

twinkle();
