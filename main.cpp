#include <iostream>
#include <cmath>

// ax + by + c = 0
double* lineA;
double* lineB;
double* lineC;
char** lineNames;

int lineLength;

//point (x, y)
double* pointX;
double* pointY;
char** pointNames;

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


//menu helper functions
void printMenu() {
    std::cout << "Choose a command:" << std::endl;
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
    std::cout << "0. Exit" << std::endl;
}

char getCommand() {
    char a;
    std::cin >> a;
    return a;
}

void operationEnd(){
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();
}


// operations
char *getValidName() {
    char *name = new char[100];
    std::cin >> name;
    for (int i = 0; name[i] != '\0' ; ++i) {
        if (!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] >= 'A' && name[i] <= 'Z') && !(name[i] >= '0' && name[i] <= '9') && name[i] != '_') {
            std::cout << "Invalid name! Try again: ";
            return getValidName();
        }
    }
    return name;
}

void addLine() {
    std::cout << "Enter line name: ";
    char* name = getValidName();
    std::cout << "Enter line coefficients: ";
    double a, b, c;
    std::cin >> a >> b >> c;
    double* tempLineA = new double[lineLength + 1];
    double* tempLineB = new double[lineLength + 1];
    double* tempLineC = new double[lineLength + 1];
    char** tempLineName = new char*[lineLength + 1];
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
}

void addPoint() {
    std::cout << "Enter point name: ";
    char* name = getValidName();
    std::cout << "Enter point coordinates: ";
    double x, y;
    std::cin >> x >> y;
    double* tempPointX = new double[pointLength + 1];
    double* tempPointY = new double[pointLength + 1];
    char** tempPointName = new char*[pointLength + 1];
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

}

void printLine(int index) {
    std::cout << lineNames[index] << ": " << lineA[index] << "x + " << lineB[index] << "y + " << lineC[index] << " = 0" << std::endl;
}

void printLines() {
    for (int i = 0; i < lineLength; i++) {
       printLine(i);
    }
}

void printPoint(int index) {
    std::cout << pointNames[index] << ": (" << pointX[index] << ", " << pointY[index] << ")" << std::endl;
}

void printPoints() {
    for (int i = 0; i < pointLength; i++) {
        printPoint(i);
    }
}


int findPoint() {
    std::cout << "Enter point name: ";
    char* name = getValidName();
    for (int i = 0; i < pointLength; i++) {
        if (strcmp(pointNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int findLine() {
    std::cout << "Enter line name: ";
    char* name = getValidName();
    for (int i = 0; i < lineLength; i++) {
        if (strcmp(lineNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

bool isLying(int lineIndex, int pointIndex){
    return lineA[lineIndex] * pointX[pointIndex] + lineB[lineIndex] * pointY[pointIndex] + lineC[lineIndex] == 0;
}

void isLying() {
    if (pointLength == 0 || lineLength == 0) {
        std::cout << "No points or lines!" << std::endl;
        operationEnd();
        return;
    }

    int pointIndex = findPoint();
    if (pointIndex == -1) {
        std::cout << "Point not found!" << std::endl;
        operationEnd();
        return;
    }

    int lineIndex = findLine();
    if (lineIndex == -1) {
        std::cout << "Line not found!" << std::endl;
        operationEnd();
        return ;
    }

    printLine(lineIndex);
    printPoint(pointIndex);
    std::cout << "Result: " << (isLying(lineIndex, pointIndex) ? "true" : "false") << std::endl;
    operationEnd();
}

void createLineFromPointAndLine() {
    if (pointLength == 0 || lineLength == 0) {
        std::cout << "No points or lines!" << std::endl;
        operationEnd();
        return;
    }

    int pointIndex = findPoint();
    if (pointIndex == -1) {
        std::cout << "Point not found!" << std::endl;
        operationEnd();
        return;
    }

    int lineIndex = findLine();
    if (lineIndex == -1) {
        std::cout << "Line not found!" << std::endl;
        operationEnd();
        return ;
    }

    // New line: a1x + b1y + c1 = 0
    // its parallel to Line: ax + by + c = 0 => a1 = a, b1 = b
    // and goes through Point: x0, y0 => c1 = -a1 * x0 - b1 * y0


    printLine(lineIndex);
    printPoint(pointIndex);
    std::cout << "Result: " << lineA[lineIndex] << "x + " << lineB[lineIndex] << "y + " << -lineA[lineIndex] * pointX[pointIndex] - lineB[lineIndex] * pointY[pointIndex] << " = 0" << std::endl;
    operationEnd();
}

void createLineFromPerpendicularLineAndCrossingPoint() {
    if (pointLength == 0 || lineLength == 0) {
        std::cout << "No points or lines!" << std::endl;
        operationEnd();
        return;
    }

    int pointIndex = findPoint();
    if (pointIndex == -1) {
        std::cout << "Point not found!" << std::endl;
        operationEnd();
        return;
    }

    int lineIndex = findLine();
    if (lineIndex == -1) {
        std::cout << "Line not found!" << std::endl;
        operationEnd();
        return ;
    }

    if (!isLying(lineIndex, pointIndex)) {
        std::cout << "Point is not lying on the line!" << std::endl;
        operationEnd();
        return;
    }

    printLine(lineIndex);
    printPoint(pointIndex);
    std::cout << "Result: " << -lineB[lineIndex] << "x + " << lineA[lineIndex] << "y + " << (lineB[lineIndex] * pointX[pointIndex] - lineA[lineIndex] * pointY[pointIndex]) << " = 0" << std::endl;
    operationEnd();
}

void twoLinesIntersection() {
    if (lineLength < 2) {
        std::cout << "Not enough lines!" << std::endl;
        operationEnd();
        return;
    }

    int lineIndex1 = findLine();
    if (lineIndex1 == -1) {
        std::cout << "Line not found!" << std::endl;
        operationEnd();
        return;
    }

    int lineIndex2 = findLine();
    if (lineIndex2 == -1) {
        std::cout << "Line not found!" << std::endl;
        operationEnd();
        return;
    }

    //if lines are parallel
    if (lineA[lineIndex1] * lineB[lineIndex2] == lineA[lineIndex2] * lineB[lineIndex1]) {
        std::cout << "Lines are parallel!" << std::endl;
        operationEnd();
        return;
    }

    // Line 1: a1x + b1y + c1 = 0
    // Line 2: a2x + b2y + c2 = 0
    // Intersection: x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1), y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)

    printLine(lineIndex1);
    printLine(lineIndex2);
    std::cout << "Result: " << "( " << (lineB[lineIndex1] * lineC[lineIndex2] - lineB[lineIndex2] * lineC[lineIndex1]) / (lineA[lineIndex1] * lineB[lineIndex2] - lineA[lineIndex2] * lineB[lineIndex1]) << ", " << (lineA[lineIndex2] * lineC[lineIndex1] - lineA[lineIndex1] * lineC[lineIndex2]) / (lineA[lineIndex1] * lineB[lineIndex2] - lineA[lineIndex2] * lineB[lineIndex1]) << ')' << std::endl;
    operationEnd();

}

void triangleLinesFromThreePoints() {
    if (pointLength < 3) {
        std::cout << "Not enough points!" << std::endl;
        operationEnd();
        return;
    }

    int pointIndex1 = findPoint();
    if (pointIndex1 == -1) {
        std::cout << "Point not found!" << std::endl;
        operationEnd();
        return;
    }

    int pointIndex2 = findPoint();
    if (pointIndex2 == -1) {
        std::cout << "Point not found!" << std::endl;
        operationEnd();
        return;
    }

    int pointIndex3 = findPoint();
    if (pointIndex3 == -1) {
        std::cout << "Point not found!" << std::endl;
        operationEnd();
        return;
    }

    std::cout<< "Point A:" << std::endl;
    printPoint(pointIndex1);
    std::cout<< "Point B:" << std::endl;
    printPoint(pointIndex2);
    std::cout<< "Point C:" << std::endl;
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

    std::cout << "Height from A to BC: " << (pointX[pointIndex3] - pointX[pointIndex2]) << "x + " << (pointY[pointIndex3] - pointY[pointIndex2]) << "y + " << (pointX[pointIndex2] - pointX[pointIndex3]) * pointX[pointIndex1] + (pointY[pointIndex2] - pointY[pointIndex3]) * pointY[pointIndex1] << " = 0" << std::endl;
    std::cout << "Height from B to CA: " << (pointX[pointIndex1] - pointX[pointIndex3]) << "x + " << (pointY[pointIndex1] - pointY[pointIndex3]) << "y + " << (pointX[pointIndex3] - pointX[pointIndex1]) * pointX[pointIndex2] + (pointY[pointIndex3] - pointY[pointIndex1]) * pointY[pointIndex2] << " = 0" << std::endl;
    std::cout << "Height from C to AB: " << (pointX[pointIndex2] - pointX[pointIndex1]) << "x + " << (pointY[pointIndex2] - pointY[pointIndex1]) << "y + " << (pointX[pointIndex1] - pointX[pointIndex2]) * pointX[pointIndex3] + (pointY[pointIndex1] - pointY[pointIndex2]) * pointY[pointIndex3] << " = 0" << std::endl;

    // median from A, B, C to  BC, CA, AB
    // middle point of AB is M(x1 + x2) / 2, (y1 + y2) / 2)
    // middle point of BC is N(x2 + x3) / 2, (y2 + y3) / 2)
    // middle point of CA is P(x3 + x1) / 2, (y3 + y1) / 2)
    // AN: (( y2 + y3 ) / 2 - y1) * x + (x1 - ( x2 + x3 ) / 2) * y + ( ( x2 + x3 ) / 2 * y1 - x1 * ( y2 + y3 ) / 2) = 0
    // BP: (( y3 + y1 ) / 2 - y2) * x + (x2 - ( x3 + x1 ) / 2) * y + ( ( x3 + x1 ) / 2 * y2 - x2 * ( y3 + y1 ) / 2) = 0
    // CM: (( y1 + y2 ) / 2 - y3) * x + (x3 - ( x1 + x2 ) / 2) * y + ( ( x1 + x2 ) / 2 * y3 - x3 * ( y1 + y2 ) / 2) = 0
    std::cout << "Median from A to BC" << ((pointY[pointIndex2] + pointY[pointIndex3]) / 2 - pointY[pointIndex1]) << "x + " << (pointX[pointIndex1] - (pointX[pointIndex2] + pointX[pointIndex3]) / 2) << "y + " << ((pointX[pointIndex2] + pointX[pointIndex3]) / 2 * pointY[pointIndex1] - pointX[pointIndex1] * (pointY[pointIndex2] + pointY[pointIndex3]) / 2) << " = 0" << std::endl;
    std::cout << "Median from B to CA" << ((pointY[pointIndex3] + pointY[pointIndex1]) / 2 - pointY[pointIndex2]) << "x + " << (pointX[pointIndex2] - (pointX[pointIndex3] + pointX[pointIndex1]) / 2) << "y + " << ((pointX[pointIndex3] + pointX[pointIndex1]) / 2 * pointY[pointIndex2] - pointX[pointIndex2] * (pointY[pointIndex3] + pointY[pointIndex1]) / 2) << " = 0" << std::endl;
    std::cout << "Median from C to AB" << ((pointY[pointIndex1] + pointY[pointIndex2]) / 2 - pointY[pointIndex3]) << "x + " << (pointX[pointIndex3] - (pointX[pointIndex1] + pointX[pointIndex2]) / 2) << "y + " << ((pointX[pointIndex1] + pointX[pointIndex2]) / 2 * pointY[pointIndex3] - pointX[pointIndex3] * (pointY[pointIndex1] + pointY[pointIndex2]) / 2) << " = 0" << std::endl;

    // perpendicular bisector from A, B, C to  BC, CA, AB
    // bisector of AB is sAB: (x - x1)^2 + (y - y1)^2 = (x - x2)^2 + (y - y2)^2
    // sAB: x^2 - 2 * x1 * x + x1^2 + y^2 - 2 * y1 * y + y1^2 = x^2 - 2 * x2 * x + x2^2 + y^2 - 2 * y2 * y + y2^2
    // sAB: 2 * (x1 - x2) * x + 2 * (y1 - y2) * y + x1^2 - x2^2 + y1^2 - y2^2 = 0
    // sBC: 2 * (x2 - x3) * x + 2 * (y2 - y3) * y + x2^2 - x3^2 + y2^2 - y3^2 = 0
    // sCA: 2 * (x3 - x1) * x + 2 * (y3 - y1) * y + x3^2 - x1^2 + y3^2 - y1^2 = 0
    std::cout << "Perpendicular bisector of AB" << ( 2 * (pointX[pointIndex1] - pointX[pointIndex2]) ) << "x + " << ( 2 * (pointY[pointIndex1] - pointY[pointIndex2]) ) << "y + " << ( pointX[pointIndex1] * pointX[pointIndex1] - pointX[pointIndex2] * pointX[pointIndex2] + pointY[pointIndex1] * pointY[pointIndex1] - pointY[pointIndex2] * pointY[pointIndex2] ) << " = 0" << std::endl;
    std::cout << "Perpendicular bisector of BC" << ( 2 * (pointX[pointIndex2] - pointX[pointIndex3]) ) << "x + " << ( 2 * (pointY[pointIndex2] - pointY[pointIndex3]) ) << "y + " << ( pointX[pointIndex2] * pointX[pointIndex2] - pointX[pointIndex3] * pointX[pointIndex3] + pointY[pointIndex2] * pointY[pointIndex2] - pointY[pointIndex3] * pointY[pointIndex3] ) << " = 0" << std::endl;
    std::cout << "Perpendicular bisector of CA" << ( 2 * (pointX[pointIndex3] - pointX[pointIndex1]) ) << "x + " << ( 2 * (pointY[pointIndex3] - pointY[pointIndex1]) ) << "y + " << ( pointX[pointIndex3] * pointX[pointIndex3] - pointX[pointIndex1] * pointX[pointIndex1] + pointY[pointIndex3] * pointY[pointIndex3] - pointY[pointIndex1] * pointY[pointIndex1] ) << " = 0" << std::endl;


}

void tangentFromParabolaAndPoint() {
    std::cout << "Enter parabola equation: y = ax^2 + bx + c" << std::endl;
    double a, b, c;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << std::endl;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << std::endl;
    std::cout << "c = ";
    std::cin >> c;
    std::cout << std::endl;
    std::cout << "Enter point coordinates: (x, 0)" << std::endl;
    double x;
    std::cout << "x = ";
    std::cin >> x;
    std::cout << std::endl;

    // tangent line equation: y = kx + b
    // 0 = (2ax + b) * (x0) + ax^2 + bx + c
    // 0 = ax^2 + (2ax0 + b)x + (bx0 + c)
    // D = (2ax0 + b)^2 - 4 * a * (bx0 + c) = (2ax0)^2 + 4abx0 + b^2 - 4abx0 - 4ac = (2ax0)^2 + b^2 - 4ac

    double D = (2 * a * x) * (2 * a * x) + b * b - 4 * a * c;
    double x1 = (-2 * a * x - b + std::sqrt(D)) / (2 * a);
    double x2 = (-2 * a * x - b - std::sqrt(D)) / (2 * a);
    double y1 = a * x1 * x1 + b * x1 + c;
    double y2 = a * x2 * x2 + b * x2 + c;

    //two points to line equation from x1, y1, x2, y2
    // (y2 - y1) * x + (x1 - x2) * y + (x2 * y1 - x1 * y2) = 0
    // line from ( x, 0) to (x1, y1)
    std::cout << "Tangent line equation: " << (y1) << "x + " << (x - x1) << "y + " << (- x * y1) << " = 0" << std::endl;
    //line from ( x, 0) to (x2, y2)
    std::cout << "Tangent line equation: " << (y2) << "x + " << (x - x2) << "y + " << (- x * y2) << " = 0" << std::endl;

    operationEnd();
}

void crossingPointsParabolaAndLine() {
    std::cout << "Enter parabola equation: y = ax^2 + bx + c" << std::endl;
    double pA, pB, pC;
    std::cout << "a = ";
    std::cin >> pA;
    std::cout << std::endl;
    std::cout << "b = ";
    std::cin >> pB;
    std::cout << std::endl;
    std::cout << "c = ";
    std::cin >> pC;
    std::cout << std::endl;
    std::cout << "Enter line equation: y = kx + d" << std::endl;
    double lK, lD;
    std::cout << "k = ";
    std::cin >> lK;
    std::cout << std::endl;
    std::cout << "d = ";
    std::cin >> lD;
    std::cout << std::endl;

    // line equation: y = kx + d
    // parabola equation: y = ax^2 + bx + c
    // 0 = ax^2 + (b - k)x + (c - d)
    double D = (pB - lK) * (pB - lK) - 4 * pA * (pC - lD);
    double x1 = (-pB + lK + std::sqrt(D)) / (2 * pA);
    double x2 = (-pB + lK - std::sqrt(D)) / (2 * pA);
    double y1 = lK * x1 + lD;
    double y2 = lK * x2 + lD;

    if (x1 != x2)
        std::cout << "Crossing points: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << std::endl;
    else
        std::cout << "Crossing point: (" << x1 << ", " << y1 << ")" << std::endl;

    operationEnd();
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
        case '0':
            running = false;
            break;
        default:
            std::cout << "Invalid command" << std::endl;
    }

}

void gameLoop() {
    while(running){
        printMenu();
        char input = getCommand();
        handleCommand(input);
    }
}

int main() {
    gameLoop();
    return 0;
}
