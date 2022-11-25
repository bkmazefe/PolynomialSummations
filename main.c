#include <stdio.h>

void readPolynomial(double coefficients[], int degrees[]){
    int skip = 0;
    for (int i = 0; i < 20; i++){
        if (skip == 0) {
            double temp = 0.0;
            printf("Enter coefficient: \n");
            scanf("%lf", &temp);

            if (1 - temp != 1) {
                coefficients[i] = temp;
                printf("Enter degree: \n");
                scanf("%d", &degrees[i]);
            } else {
                skip = 1;
                coefficients[i] = 0.0;
            }
        } else {
            coefficients[i] = 0.0;
            degrees[i] = 0;
        }
    }
    return;
}

void printPolynomial(double coefficients[], int degrees[]) {
    for (int i = 19; i >= 0; i--) {
        if (1 - coefficients[i] == 1) {
            continue;
        }

        if (coefficients[i] < 0 && degrees[i] != 0) {
            printf("-");
        }

        if (degrees[i] != 0) {
            if (coefficients[i] == 1 || coefficients[i] == -1) {
                printf("x");
            } else {
                if (coefficients[i] < 0) {
                    printf("%.fx", coefficients[i] * -1);
                } else {
                    printf("%.fx", coefficients[i]);
                }
            }
            if (degrees[i] != 1) {
                printf("^%d", degrees[i]);
            }

        } else {
            printf("1");
        }
        if (i-1 >= 0) {
            if (coefficients[i-1] > 0 || degrees[i-1] == 0) {
                printf("+");
            }
        }
    }

    printf("\n");
    return;
}

//////////////////////////////////////////////
void double_tween(double arr[], double value, int pos){
    for (int i = 19; i>pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos] = value;
    return;
}

void int_tween(int arr[], int value, int pos){
    for (int i = 19; i>=pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos] = value;

    for (int i = 0; i<20; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

void int_remove(int arr[], int pos){
    for (int i = pos; i<20; i++){
        arr[i] = arr[i+1];
    }
    return;
}

void double_remove(double arr[], int pos){
    for (int i = pos; i<20; i++){
        arr[i] = arr[i+1];
    }
    return;
}
//////////////////////////////////////////////

void addPolynomials(double c1[], int d1[], double c2[], int d2[], double c3[], int d3[]) {
    for (int i = 0; i<20; i++){
        d3[i] = d1[i];
        c3[i] = c1[i];
    }

    for (int i = 0; i<20; i++){
        if (1 - c2[i] == 1){
            break;
        }

        for (int x = 0; x<20; x++) {
            int lastHigh = x;
            if (d2[i] > d3[x]) {
                if (1 - c3[x] != 1 ){
                    lastHigh = x + 1;
                } else {
                    int_tween(d3, d2[i], lastHigh);
                    double_tween(c3, c2[i], lastHigh);
                    break;
                }
            } else if (d2[i] < d3[x]) {
                int_tween(d3, d2[i], lastHigh);
                double_tween(c3, c2[i], lastHigh);
                break;
            } else {
                c3[x] = c3[x] + c2[i];
                if (1 - c3[x] == 1) {
                    int_remove(d3, x);
                    double_remove(c3, x);
                }
                break;
            }
        }
    }
}

int main() {
    double c1[20] = {};
    int d1[20] = {};
    double c2[20] = {};
    int d2[20] = {};
    double c3[20] = {};
    int d3[20] = {};

    readPolynomial(c1, d1);
    printPolynomial(c1, d1);

    readPolynomial(c2, d2);
    printPolynomial(c2, d2);

    addPolynomials(c1, d1, c2, d2, c3, d3);

    printPolynomial(c3, d3);

    return 0;
}
