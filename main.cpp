/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Milen Valev
* @idnumber 0MI0600178
* @compiler GCC
*
* Geometry tool main file
*
*/

#include <iostream>
#include <cmath>

// ax + by + c = 0
double *lineA;
double *lineB;
double *lineC;
char **lineNames;

int lineLength;

//point (x, y)
double *pointX;
double *pointY;
char **pointNames;

int pointLength;

bool running = true;

//helper functions
int strcmp(char *string, char *name) {
    int i = 0;
    while (string[i] != '\0' && name[i] != '\0') {
        if (string[i] != name[i]) {
            return string[i] - name[i];
        }
        i++;
    }
    if (string[i] == '\0' && name[i] == '\0') {
        return 0;
    }
    return string[i] - name[i];
}

void printLine(double a, double b, double c) {
    std::cout << a << "x"
              << (b < 0 ? " " : " +") << b << "y"
              << (c < 0 ? " " : " +") << c << " = 0"
              << std::endl;
}

void printLine(int index) {
    std::cout << lineNames[index] << ": ";
    printLine(lineA[index], lineB[index], lineC[index]);
}

void printPoint(int index) {
    std::cout << pointNames[index] << ": (" << pointX[index] << ", " << pointY[index] << ")" << std::endl;
}

void getLineCoordinates(double &a, double &b, double &c) {
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "c = ";
    std::cin >> c;
}


//menu helper functions
void printMenu() {
    std::cout << "Choose a command:" << std::endl;
    std::cout << "Commands with numbers (1 - 9) gets as input name of an existing point or line!" << std::endl;
    std::cout << "1. Add a line" << std::endl;
    std::cout << "2. Add a point" << std::endl;
    std::cout << "3. Print all lines" << std::endl;
    std::cout << "4. Print all points" << std::endl;
    std::cout << "5. Is a point lying on a line?" << std::endl;
    std::cout << "6. Create Line passing through point and parallel to another line" << std::endl;
    std::cout << "7. Create Line perpendicular to Line G and with crossing point Point P" << std::endl;
    std::cout << "8. Find 2 lines crossing point" << std::endl;
    std::cout << "9. Find Heights, medium and bisector from triangle created by 3 points" << std::endl;
    std::cout << "A. Find tangent from parabola and a point" << std::endl;
    std::cout << "B. Find crossing points of parabola and a line" << std::endl;
    std::cout << "C. Find quadrilateral type from 4 lines (lines should be in right order to create a quadrilateral)"
              << std::endl;
    std::cout << "0. Exit" << std::endl;
}

char getCommand() {
    char a;
    std::cin >> a;
    return a;
}

void operationEnd() {
    std::cin.ignore();
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore();
}


// operations
char *getValidName() {
    char *name = new char[100];
    std::cin >> name;
    for (int i = 0; name[i] != '\0'; ++i) {
        if (!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] >= 'A' && name[i] <= 'Z') &&
            !(name[i] >= '0' && name[i] <= '9') && name[i] != '_') {
            std::cout << "Invalid name! \nTry again: ";
            return getValidName();
        }
    }
    return name;
}

void addLine() {
    std::cout << "Enter line name: ";
    char *name = getValidName();
    std::cout << "Enter line coefficients ( ax + by + c = 0): " << std::endl;
    double a, b, c;
    getLineCoordinates(a, b, c);
    double *tempLineA = new double[lineLength + 1];
    double *tempLineB = new double[lineLength + 1];
    double *tempLineC = new double[lineLength + 1];
    char **tempLineName = new char *[lineLength + 1];
    for (int i = 0; i < lineLength; i++) {
        tempLineA[i] = lineA[i];
        tempLineB[i] = lineB[i];
        tempLineC[i] = lineC[i];
        tempLineName[i] = lineNames[i];
    }
    tempLineA[lineLength] = a;
    tempLineB[lineLength] = b;
    tempLineC[lineLength] = c;
    tempLineName[lineLength] = name;
    lineLength++;

    delete[] lineA;
    delete[] lineB;
    delete[] lineC;
    delete[] lineNames;

    lineA = tempLineA;
    lineB = tempLineB;
    lineC = tempLineC;
    lineNames = tempLineName;
    printLine(lineLength - 1);
}

void addPoint() {
    std::cout << "Enter point name: ";
    char *name = getValidName();
    std::cout << std::endl << "Enter point coordinates ( x, y): " << std::endl;
    double x, y;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    double *tempPointX = new double[pointLength + 1];
    double *tempPointY = new double[pointLength + 1];
    char **tempPointName = new char *[pointLength + 1];
    for (int i = 0; i < pointLength; i++) {
        tempPointX[i] = pointX[i];
        tempPointY[i] = pointY[i];
        tempPointName[i] = pointNames[i];
    }
    tempPointX[pointLength] = x;
    tempPointY[pointLength] = y;
    tempPointName[pointLength] = name;
    pointLength++;

    delete[] pointX;
    delete[] pointY;
    delete[] pointNames;

    pointX = tempPointX;
    pointY = tempPointY;
    pointNames = tempPointName;

    printPoint(pointLength - 1);
}


void printLines() {
    for (int i = 0; i < lineLength; i++) {
        printLine(i);
    }
}

void printPoints() {
    for (int i = 0; i < pointLength; i++) {
        printPoint(i);
    }
}


int findPoint() {
    std::cout << "Enter point name: ";
    char *name = getValidName();
    for (int i = 0; i < pointLength; i++) {
        if (strcmp(pointNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int findLine() {
    std::cout << "Enter line name: ";
    char *name = getValidName();
    for (int i = 0; i < lineLength; i++) {
        if (strcmp(lineNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

bool isLying(int lineIndex, int pointIndex) {
    return lineA[lineIndex] * pointX[pointIndex] + lineB[lineIndex] * pointY[pointIndex] + lineC[lineIndex] == 0;
}

void isLying() {
    if (pointLength == 0 || lineLength == 0) {
        std::cout << "No points or lines!" << std::endl;

        return;
    }

    int pointIndex = findPoint();
    if (pointIndex == -1) {
        std::cout << "Point not found!" << std::endl;

        return;
    }

    int lineIndex = findLine();
    if (lineIndex == -1) {
        std::cout << "Line not found!" << std::endl;

        return;
    }

    printLine(lineIndex);
    printPoint(pointIndex);
    std::cout << "Result: " << (isLying(lineIndex, pointIndex) ? "true" : "false") << std::endl;

}

void createLineFromPointAndLine() {
    if (pointLength == 0 || lineLength == 0) {
        std::cout << "No points or lines!" << std::endl;

        return;
    }

    int pointIndex = findPoint();
    if (pointIndex == -1) {
        std::cout << "Point not found!" << std::endl;

        return;
    }

    int lineIndex = findLine();
    if (lineIndex == -1) {
        std::cout << "Line not found!" << std::endl;

        return;
    }

    // New line: a1x + b1y + c1 = 0
    // its parallel to Line: ax + by + c = 0 => a1 = a, b1 = b
    // and goes through Point: x0, y0 => c1 = -a1 * x0 - b1 * y0


    printLine(lineIndex);
    printPoint(pointIndex);
    std::cout << "Result: ";
    printLine(lineA[lineIndex], lineB[lineIndex],
              -lineA[lineIndex] * pointX[pointIndex] - lineB[lineIndex] * pointY[pointIndex]);
}

void createLineFromPerpendicularLineAndCrossingPoint() {
    if (pointLength == 0 || lineLength == 0) {
        std::cout << "No points or lines!" << std::endl;
        return;
    }

    int pointIndex = findPoint();
    if (pointIndex == -1) {
        std::cout << "Point not found!" << std::endl;
        return;
    }

    int lineIndex = findLine();
    if (lineIndex == -1) {
        std::cout << "Line not found!" << std::endl;
        return;
    }

    if (!isLying(lineIndex, pointIndex)) {
        std::cout << "Point is not lying on the line!" << std::endl;
        return;
    }

    printLine(lineIndex);
    printPoint(pointIndex);
    std::cout << "Result: ";
    printLine(-lineB[lineIndex], lineA[lineIndex],
              lineB[lineIndex] * pointX[pointIndex] - lineA[lineIndex] * pointY[pointIndex]);

}

void twoLinesIntersection() {
    if (lineLength < 2) {
        std::cout << "Not enough lines!" << std::endl;
        return;
    }

    int lineIndex1 = findLine();
    if (lineIndex1 == -1) {
        std::cout << "Line not found!" << std::endl;
        return;
    }

    int lineIndex2 = findLine();
    if (lineIndex2 == -1) {
        std::cout << "Line not found!" << std::endl;
        return;
    }

    //if lines are parallel
    if (lineA[lineIndex1] * lineB[lineIndex2] == lineA[lineIndex2] * lineB[lineIndex1]) {
        std::cout << "Lines are parallel!" << std::endl;
        return;
    }

    // Line 1: a1x + b1y + c1 = 0
    // Line 2: a2x + b2y + c2 = 0
    // Intersection: x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1), y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)

    printLine(lineIndex1);
    printLine(lineIndex2);
    std::cout << "Result: " << "( " << (lineB[lineIndex1] * lineC[lineIndex2] - lineB[lineIndex2] * lineC[lineIndex1]) /
                                       (lineA[lineIndex1] * lineB[lineIndex2] - lineA[lineIndex2] * lineB[lineIndex1])
              << ", " << (lineA[lineIndex2] * lineC[lineIndex1] - lineA[lineIndex1] * lineC[lineIndex2]) /
                         (lineA[lineIndex1] * lineB[lineIndex2] - lineA[lineIndex2] * lineB[lineIndex1]) << ')'
              << std::endl;
}

bool isSamePoint(int index1, int index2) {
    return pointX[index1] == pointX[index2] && pointY[index1] == pointY[index2];
}

void triangleLinesFromThreePoints() {
    if (pointLength < 3) {
        std::cout << "Not enough points!" << std::endl;
        return;
    }

    int pointIndex1 = findPoint();
    if (pointIndex1 == -1) {
        std::cout << "Point not found!" << std::endl;
        return;
    }

    int pointIndex2 = findPoint();
    if (pointIndex2 == -1) {
        std::cout << "Point not found!" << std::endl;
        return;
    }

    int pointIndex3 = findPoint();
    if (pointIndex3 == -1) {
        std::cout << "Point not found!" << std::endl;
        return;
    }

    if (isSamePoint(pointIndex1, pointIndex2) || isSamePoint(pointIndex1, pointIndex3) ||
        isSamePoint(pointIndex2, pointIndex3)) {
        std::cout << "Points are the same!" << std::endl;
        return;
    }

    std::cout << "Point A:" << std::endl;
    printPoint(pointIndex1);
    std::cout << "Point B:" << std::endl;
    printPoint(pointIndex2);
    std::cout << "Point C:" << std::endl;
    printPoint(pointIndex3);

    // triangle ABC with points A(x1, y1), B(x2, y2), C(x3, y3)
    // AB: (y2 - y1) * x + (x1 - x2) * y + (x2 * y1 - x1 * y2) = 0
    // BC: (y3 - y2) * x + (x2 - x3) * y + (x3 * y2 - x2 * y3) = 0
    // CA: (y1 - y3) * x + (x3 - x1) * y + (x1 * y3 - x3 * y1) = 0

    // heights from A, B, C to  BC, CA, AB
    // hA from point A to line BC
    // hA: ax + by + c = 0
    // ha perpendicular to BC => a = x3 - x2, b = y3 - y2
    // ha: (x3 - x2) * x + (y3 - y2) * y + c = 0
    // ha goes through point A => c = -a * x1 - b * y1 = (x2 - x3) * x1 + (y2 - y3) * y1
    // hA: (x3 - x2) * x + (y3 - y2) * y + (x2 - x3) * x1 + (y2 - y3) * y1 = 0

    // analogously for hB and hC
    // hB: (x1 - x3) * x + (y1 - y3) * y + (x3 - x1) * x2 + (y3 - y1) * y2 = 0
    // hC: (x2 - x1) * x + (y2 - y1) * y + (x1 - x2) * x3 + (y1 - y2) * y3 = 0

    std::cout << "Height from A to BC: ";
    printLine(pointX[pointIndex3] - pointX[pointIndex2], pointY[pointIndex3] - pointY[pointIndex2],
              (pointX[pointIndex2] - pointX[pointIndex3]) * pointX[pointIndex1] +
              (pointY[pointIndex2] - pointY[pointIndex3]) * pointY[pointIndex1]);
    std::cout << "Height from B to CA: ";
    printLine(pointX[pointIndex1] - pointX[pointIndex3], pointY[pointIndex1] - pointY[pointIndex3],
              (pointX[pointIndex3] - pointX[pointIndex1]) * pointX[pointIndex2] +
              (pointY[pointIndex3] - pointY[pointIndex1]) * pointY[pointIndex2]);
    std::cout << "Height from C to AB: ";
    printLine(pointX[pointIndex2] - pointX[pointIndex1], pointY[pointIndex2] - pointY[pointIndex1],
              (pointX[pointIndex1] - pointX[pointIndex2]) * pointX[pointIndex3] +
              (pointY[pointIndex1] - pointY[pointIndex2]) * pointY[pointIndex3]);

    // median from A, B, C to  BC, CA, AB
    // middle point of AB is M(x1 + x2) / 2, (y1 + y2) / 2)
    // middle point of BC is N(x2 + x3) / 2, (y2 + y3) / 2)
    // middle point of CA is P(x3 + x1) / 2, (y3 + y1) / 2)
    // AN: (( y2 + y3 ) / 2 - y1) * x + (x1 - ( x2 + x3 ) / 2) * y + ( ( x2 + x3 ) / 2 * y1 - x1 * ( y2 + y3 ) / 2) = 0
    // BP: (( y3 + y1 ) / 2 - y2) * x + (x2 - ( x3 + x1 ) / 2) * y + ( ( x3 + x1 ) / 2 * y2 - x2 * ( y3 + y1 ) / 2) = 0
    // CM: (( y1 + y2 ) / 2 - y3) * x + (x3 - ( x1 + x2 ) / 2) * y + ( ( x1 + x2 ) / 2 * y3 - x3 * ( y1 + y2 ) / 2) = 0
    std::cout << "Median from A to BC: ";
    printLine((pointY[pointIndex2] + pointY[pointIndex3]) / 2 - pointY[pointIndex1],
              (pointX[pointIndex1] - ((pointX[pointIndex2] + pointX[pointIndex3]) / 2)),
              ((pointX[pointIndex2] + pointX[pointIndex3]) / 2) * pointY[pointIndex1] -
              pointX[pointIndex1] * (pointY[pointIndex2] + pointY[pointIndex3]) / 2);
    std::cout << "Median from B to CA: ";
    printLine(((pointY[pointIndex1] + pointY[pointIndex2]) / 2) - pointY[pointIndex3],
              (pointX[pointIndex3] - ((pointX[pointIndex1] + pointX[pointIndex2]) / 2)),
              ((pointX[pointIndex1] + pointX[pointIndex2]) / 2) * pointY[pointIndex3] -
              pointX[pointIndex3] * (pointY[pointIndex1] + pointY[pointIndex2]) / 2);
    std::cout << "Median from C to AB: ";
    printLine((pointY[pointIndex1] + pointY[pointIndex2]) / 2 - pointY[pointIndex3],
              (pointX[pointIndex3] - ((pointX[pointIndex1] + pointX[pointIndex2]) / 2)),
              ((pointX[pointIndex1] + pointX[pointIndex2]) / 2) * pointY[pointIndex3] -
              pointX[pointIndex3] * (pointY[pointIndex1] + pointY[pointIndex2]) / 2);

    // perpendicular bisector from A, B, C to  BC, CA, AB
    // bisector of AB is sAB: (x - x1)^2 + (y - y1)^2 = (x - x2)^2 + (y - y2)^2
    // sAB: x^2 - 2 * x1 * x + x1^2 + y^2 - 2 * y1 * y + y1^2 = x^2 - 2 * x2 * x + x2^2 + y^2 - 2 * y2 * y + y2^2
    // sAB: 2 * (x1 - x2) * x + 2 * (y1 - y2) * y + x1^2 - x2^2 + y1^2 - y2^2 = 0
    // sBC: 2 * (x2 - x3) * x + 2 * (y2 - y3) * y + x2^2 - x3^2 + y2^2 - y3^2 = 0
    // sCA: 2 * (x3 - x1) * x + 2 * (y3 - y1) * y + x3^2 - x1^2 + y3^2 - y1^2 = 0
    std::cout << "Perpendicular bisector of AB: ";
    printLine(2 * (pointX[pointIndex1] - pointX[pointIndex2]),
              2 * (pointY[pointIndex1] - pointY[pointIndex2]),
              pointX[pointIndex1] * pointX[pointIndex1] - pointX[pointIndex2] * pointX[pointIndex2] +
              pointY[pointIndex1] * pointY[pointIndex1] - pointY[pointIndex2] * pointY[pointIndex2]);
    std::cout << "Perpendicular bisector of BC: ";
    printLine(2 * (pointX[pointIndex2] - pointX[pointIndex3]),
              2 * (pointY[pointIndex2] - pointY[pointIndex3]),
              pointX[pointIndex2] * pointX[pointIndex2] - pointX[pointIndex3] * pointX[pointIndex3] +
              pointY[pointIndex2] * pointY[pointIndex2] - pointY[pointIndex3] * pointY[pointIndex3]);
    std::cout << "Perpendicular bisector of CA: ";
    printLine(2 * (pointX[pointIndex3] - pointX[pointIndex1]),
              2 * (pointY[pointIndex3] - pointY[pointIndex1]),
              pointX[pointIndex3] * pointX[pointIndex3] - pointX[pointIndex1] * pointX[pointIndex1] +
              pointY[pointIndex3] * pointY[pointIndex3] - pointY[pointIndex1] * pointY[pointIndex1]);
}

void tangentFromParabolaAndPoint() {
    std::cout << "Enter parabola equation: y = ax^2 + bx + c" << std::endl;
    double a, b, c;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "c = ";
    std::cin >> c;

    if (a == 0) {
        std::cout << "It is not a parabola" << std::endl;
        return;
    }

    std::cout << "Enter point coordinates: (x, 0)" << std::endl;
    double x;
    std::cout << "x = ";
    std::cin >> x;

    // tangent line equation: y = kx + d
    // 0 = (2ax + b) * (x0) + c - ax^2
    // 0 = -ax^2 + 2a(x0)x + b(x0) + c
    // D = (a(x0))^2 + a * (c + b(x0))

    double D = (a * x) * (a * x) + a * (c + b * x);
    if (D < 0) {
        std::cout << "No tangent line" << std::endl;
        return;
    }
    double x1 = (-a * x - b + std::sqrt(D)) / (-a);
    double x2 = (-a * x - b - std::sqrt(D)) / (-a);
    double y1 = a * x1 * x1 + b * x1 + c;
    double y2 = a * x2 * x2 + b * x2 + c;

    //two points to line equation from x1, y1, x2, y2
    // (y2 - y1) * x + (x1 - x2) * y + (x2 * y1 - x1 * y2) = 0
    // line from ( x, 0) to (x1, y1)
    std::cout << "Tangent line equation: ";
    printLine(y1, x - x1, -x * y1);

    if (x1 == x2){
        return;
    }

    //line from ( x, 0) to (x2, y2)
    std::cout << "Tangent line equation: ";
    printLine(y2, x - x2, -x * y2);


}

void crossingPointsParabolaAndLine() {
    std::cout << "Enter parabola equation: y = ax^2 + bx + c" << std::endl;
    double pA, pB, pC;
    std::cout << "a = ";
    std::cin >> pA;
    std::cout << "b = ";
    std::cin >> pB;
    std::cout << "c = ";
    std::cin >> pC;

    if (pA == 0) {
        std::cout << "It is not a parabola" << std::endl;
        return;
    }

    std::cout << "Enter line equation: y = kx + d" << std::endl;
    double lK, lD;
    std::cout << "k = ";
    std::cin >> lK;
    std::cout << "d = ";
    std::cin >> lD;

    // line equation: y = kx + d
    // parabola equation: y = ax^2 + bx + c
    // 0 = ax^2 + (b - k)x + (c - d)
    double D = (pB - lK) * (pB - lK) - 4 * pA * (pC - lD);
    if (D < 0) {
        std::cout << "No crossing points" << std::endl;
        return;
    }
    double x1 = (-pB + lK + std::sqrt(D)) / (2 * pA);
    double x2 = (-pB + lK - std::sqrt(D)) / (2 * pA);
    double y1 = lK * x1 + lD;
    double y2 = lK * x2 + lD;

    if (x1 != x2)
        std::cout << "Crossing points: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << std::endl;
    else
        std::cout << "Crossing point: (" << x1 << ", " << y1 << ")" << std::endl;

}

bool isSame(double a1, double b1, double c1, double a2, double b2, double c2) {
    return (a1 == a2 && b1 == b2 && c1 == c2);
}

bool isSame(double a[4], double b[4], double c[4]) {

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (isSame(a[i], b[i], c[i], a[j], b[j], c[j]))
                return true;
        }
    }

    return false;
}

bool isParallel(const double a[4], const double b[4], int i, int j) {
    return a[i] * b[j] == b[i] * a[j];
}

void quadrilateralType() {
    double a[4], b[4], c[4];
    std::cout << "Enter first line equation: ax + by + c = 0" << std::endl;
    getLineCoordinates(a[0], b[0], c[0]);
    std::cout << "Enter second line equation: ax + by + c = 0" << std::endl;
    getLineCoordinates(a[1], b[1], c[1]);
    std::cout << "Enter third line equation: ax + by + c = 0" << std::endl;
    getLineCoordinates(a[2], b[2], c[2]);
    std::cout << "Enter fourth line equation: ax + by + c = 0" << std::endl;
    getLineCoordinates(a[3], b[3], c[3]);

    if (isSame(a, b, c)) {
        std::cout << "Not quadrilateral" << std::endl;
        return;
    }

    if (isParallel(a, b, 0, 1) || isParallel(a, b, 2, 3)) {
        std::cout << "Not quadrilateral" << std::endl;
        return;
    }

    //line1: a1 * x + b1 * y + c1 = 0
    //line2: a2 * x + b2 * y + c2 = 0
    // Intersection: x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1), y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)
    double intersectionX[4] = {
            //line0 and line1 intersection
            (b[0] * c[1] - b[1] * c[0]) / (a[0] * b[1] - a[1] * b[0]),
            //line1 and line2 intersection
            (b[1] * c[2] - b[2] * c[1]) / (a[1] * b[2] - a[2] * b[1]),
            //line2 and line3 intersection
            (b[2] * c[3] - b[3] * c[2]) / (a[2] * b[3] - a[3] * b[2]),
            //line3 and line0 intersection
            (b[3] * c[0] - b[0] * c[3]) / (a[3] * b[0] - a[0] * b[3])
    };
    double intersectionY[4] = {
            //line0 and line1 intersection
            (a[1] * c[0] - a[0] * c[1]) / (a[0] * b[1] - a[1] * b[0]),
            //line1 and line2 intersection
            (a[2] * c[1] - a[1] * c[2]) / (a[1] * b[2] - a[2] * b[1]),
            //line2 and line3 intersection
            (a[3] * c[2] - a[2] * c[3]) / (a[2] * b[3] - a[3] * b[2]),
            //line3 and line0 intersection
            (a[0] * c[3] - a[3] * c[0]) / (a[3] * b[0] - a[0] * b[3])
    };

    if (!isParallel(a, b, 0, 2) && !isParallel(a, b, 1, 3)) {
        std::cout << "Quadrilateral" << std::endl;
    }

    if ((isParallel(a, b, 0, 2) && !isParallel(a, b, 1, 3)) || (!isParallel(a, b, 0, 2) && isParallel(a, b, 1, 3))) {
        std::cout << "Trapezoid" << std::endl;
        return;
    }


    double diagonal1 = (intersectionX[0] - intersectionX[2]) * (intersectionX[0] - intersectionX[2]) +
                       (intersectionY[0] - intersectionY[2]) * (intersectionY[0] - intersectionY[2]);
    double diagonal2 = (intersectionX[1] - intersectionX[3]) * (intersectionX[1] - intersectionX[3]) +
                       (intersectionY[1] - intersectionY[3]) * (intersectionY[1] - intersectionY[3]);
    double diagonalScalar = (intersectionX[0] - intersectionX[2]) * (intersectionX[1] - intersectionX[3]) +
                            (intersectionY[0] - intersectionY[2]) * (intersectionY[1] - intersectionY[3]);

    if (diagonalScalar == 0 && diagonal1 == diagonal2) {
        std::cout << "Square" << std::endl;
        return;
    }

    if (diagonal1 == diagonal2) {
        std::cout << "Rectangle" << std::endl;
        return;
    }

    if (diagonalScalar == 0) {
        std::cout << "Rhombus" << std::endl;
        return;
    }

    std::cout << "Parallelogram" << std::endl;
}

// core functions
void handleCommand(char input) {
    switch (input) {
        case '1':
            addLine();
            break;
        case '2':
            addPoint();
            break;
        case '3':
            printLines();
            break;
        case '4':
            printPoints();
            break;
        case '5':
            isLying();
            break;
        case '6':
            createLineFromPointAndLine();
            break;
        case '7':
            createLineFromPerpendicularLineAndCrossingPoint();
            break;
        case '8':
            twoLinesIntersection();
            break;
        case '9':
            triangleLinesFromThreePoints();
            break;
        case 'A':
            tangentFromParabolaAndPoint();
            break;
        case 'B':
            crossingPointsParabolaAndLine();
            break;
        case 'C':
            quadrilateralType();
            break;
        case '0':
            running = false;
            break;
        default:
            std::cout << "Invalid command" << std::endl;
    }
}

void programLoop() {
    while (running) {
        printMenu();
        char input = getCommand();
        handleCommand(input);
        operationEnd();
    }
}

void clearMemory() {
    delete[] pointX;
    delete[] pointY;
    delete[] pointNames;

    delete[] lineA;
    delete[] lineB;
    delete[] lineC;
    delete[] lineNames;
}

int main() {
    programLoop();
    clearMemory();
    return 0;
}
