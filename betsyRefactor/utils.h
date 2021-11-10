#ifndef UTILS_H
#define UTILS_H

#include <FastLED.h>

#define NUM_ROWS      27
#define NUM_COLUMNS   31
#define RADIUS        16

CRGB leds[NUM_ROWS][NUM_COLUMNS];
CHSV ledsCHSV[NUM_ROWS][NUM_COLUMNS];


int leftBound[] = {7, 7, 6, 5, 5, 4, 4, 3, 3, 2, 1, 1, 0, 0,
                   0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 7};

int numLeds[] = {17, 17, 19, 21, 21, 23, 23, 25, 25, 27, 29, 29, 31, 31,
                 31, 29, 29, 27, 25, 25, 23, 23, 21, 21, 19, 17, 17};

struct px {
  double row;
  double col;
  int rowInt() {
    return (int)row;
  }
  int colInt() {
    return (int)col;
  }
  bool inBounds() {
    return rowInt() >= 0 &&
           rowInt() < NUM_ROWS &&
           col >= leftBound[rowInt()] &&
           col < (leftBound[rowInt()] + numLeds[rowInt()]);
  }
  px getRounded(int deg) {
    if ((deg >= 0 && deg < 90) || (deg > 180 && deg < 270)) {
      return {floor(row), ceil(col)};
    } else {
      return {floor(row), floor(col)};
    }
  }
};

struct Line {
  px p1;
  px p2;
};

px ORIGIN = {NUM_ROWS / 2, NUM_COLUMNS / 2};

// The vertices of each corner of the hexagon (zero-indexed)
// Intentionally smaller than the capacity of all LEDs so that the paintbrush
// bounces off the edges without overlapping at all
px TOP_LEFT = {1, 8};
px TOP_RIGHT = {1, 22};
px MIDDLE_LEFT = {13, 1};
px MIDDLE_RIGHT = {13, 29};
px BOTTOM_LEFT = {25, 8};
px BOTTOM_RIGHT = {25, 22};
Line EDGE_0 = {TOP_LEFT, TOP_RIGHT};
Line EDGE_1 = {TOP_RIGHT, MIDDLE_RIGHT};
Line EDGE_2 = {MIDDLE_RIGHT, BOTTOM_RIGHT};
Line EDGE_3 = {BOTTOM_RIGHT, BOTTOM_LEFT};
Line EDGE_4 = {BOTTOM_LEFT, MIDDLE_LEFT};
Line EDGE_5 = {MIDDLE_LEFT, TOP_LEFT};
Line EDGES[] = {EDGE_0, EDGE_1, EDGE_2, EDGE_3, EDGE_4, EDGE_5};

px pointOnCircumference(double radius, px origin, double d) {
  double degs = (d - 90 < 0) ? (d + 270) : (d - 90);
  double rads = degs * PI / 180;
  return {
    origin.row + radius * sin(rads),
    origin.col + radius * cos(rads)
  };
}

px pointOnLine(px p1, px p2, float howFar) {
  return {
    p1.row + (p2.row - p1.row) * howFar,
    p1.col + (p2.col - p1.col) * howFar
  };
}

/* Given a point, returns the reflection of that point over a line
 * Source: https://stackoverflow.com/questions/3306838
 */
px reflectPxOverLine(px p1, Line line) {
  float slope = (line.p2.row - line.p1.row) / (line.p2.col - line.p1.col);
  float yIntercept = (line.p2.col * line.p1.row - line.p1.col * line.p2.row) / (line.p2.col - line.p1.col);
  float d = (p1.col + (p1.row - yIntercept) * slope) / (1 + pow(slope, 2));
  return {
    2 * d * slope - p1.row + 2 * yIntercept,
    2 * d - p1.col
  };
}

float det(px a, px b) {
  return a.col * b.row - a.row * b.col;
}

bool doLinesIntersect(Line line1, Line line2) {
  px colDiff = {line2.p1.col - line2.p2.col, line1.p1.col - line1.p2.col};
  px rowDiff = {line2.p1.row - line2.p2.row, line1.p1.row - line1.p2.row};
  return det(colDiff, rowDiff) != 0;
}

/* Returns the point where two lines intersect
 * Source: https://stackoverflow.com/questions/20677795
 */
px pxLinesIntersect(Line line1, Line line2) {
  px colDiff = {line2.p1.col - line2.p2.col, line1.p1.col - line1.p2.col};
  px rowDiff = {line2.p1.row - line2.p2.row, line1.p1.row - line1.p2.row};
  float div = det(colDiff, rowDiff);
  px d = {det(line2.p1, line2.p2), det(line1.p1, line1.p2)};
  return {
    det(d, rowDiff) / div,
    det(d, colDiff) / div
  };
}

void allBlack() {
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLUMNS; col++) {
      leds[row][col] = CHSV(0, 0, 0);
    }
  }
}

float distance(px p1, px p2) {
  return (float)sqrt(pow((p1.col - p2.col), 2) + pow((p1.row - p2.row), 2));
}

float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

int rollingInc(int current, int max) {
  return current < (max - 1) ? current + 1 : 0;
}

#endif
