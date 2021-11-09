double TENSION = 55.0; // the tension in the strings
double SPACING = 10.0; // the distance between masses on the string
double MASS = 0.005; // the mass of each pixel
double MAX_POSITION = SPACING / 100.0;
double MIN_POSITION = (-1 * SPACING) / 100.0;
double GAMMA = .0185; // the damping constant (without this the waves will reflect off the free end and continue forever)
double NUM_COLORS = 200; // the number of shades of blue
double TSTEP = .0015;

struct Water {
  double _position[NUM_ROWS][NUM_COLUMNS];
  double _velocity[NUM_ROWS][NUM_COLUMNS];

  Water() {
    for (int row = 0; row < NUM_ROWS; row++) {
      for (int col = 0; col < NUM_COLUMNS; col++) {
        _position[row][col] = mapf(random(0, 100), 0, 100, MIN_POSITION, MAX_POSITION);
        _velocity[row][col] = 0;
      }
    }
  }

  Water play() {
    _showWater();
    return *this;
  }

  void _showWater() {
    for (int row = 0; row < NUM_ROWS; row++) {
      for (int col = 0; col < NUM_COLUMNS; col++) {
        double positionTerm = 0;

        // above
        if (row > 0) {
          positionTerm += _position[row][col] - _position[row - 1][col];
        }
        // below
        if (row < (NUM_ROWS - 1)) {
          positionTerm += _position[row][col] - _position[row + 1][col];
        }
        // left
        if (col > 0) {
          positionTerm += _position[row][col] - _position[row][col - 1];
        }
        // right
        if (col < (NUM_COLUMNS - 1)) {
          positionTerm += _position[row][col] - _position[row][col + 1];
        }

        _position[row][col] = _position[row][col] > MAX_POSITION
          ? MAX_POSITION
          : _position[row][col];
        _position[row][col] = _position[row][col] < MIN_POSITION
          ? MIN_POSITION
          : _position[row][col];

        // calculate the force as the sum of the z-component of the tensions minus the damping
        double damping = GAMMA * _velocity[row][col];
        double force = -(TENSION / SPACING) * positionTerm - damping;

        // update the position and velocity
        _position[row][col] = _position[row][col] + (_velocity[row][col] * TSTEP) + 0.5
          * (force / MASS) * TSTEP * TSTEP;
        _velocity[row][col] = _velocity[row][col] + (force / MASS) * TSTEP;

        // assign color to the pixel according to the position and velocity
        float colorIndex = mapf(_position[row][col], MIN_POSITION, MAX_POSITION, 0, NUM_COLORS);
        CHSV color = colorIndex < NUM_COLORS / 2 ? CHSV_BLUE : CHSV_WHITE;
        color.v = mapf(abs((NUM_COLORS / 2) - colorIndex), 0, NUM_COLORS / 2, 0, 255);
        leds[row][col] = color;
      }
    }
    FastLED.show();
  }
};
