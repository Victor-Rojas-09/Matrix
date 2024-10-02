//Victor Manuel Rojas Trejos 
//Operaciones con Matrices
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> EnterMatrix(){
  unsigned int row, column;
  bool valid = false;  
  do{
    cout << "Entra el numero de filas: ";
    cin >> row;
    cout << "Entra el numero de columnas: ";
    cin >> column;

    if((column < 1 || row) < 1 && (column > 200 || row > 200)){
      cout << "The number of rows and columns is vey big, try again\n";
    }
    else{
      valid = true;
    }
  }while(valid != true);
  vector<vector<int>> matrix(row, vector<int>(column));

  for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
      int num;
      cout << "Enter the value of the position [" << i << "][" << j << "]: ";
      cin >> num;
      if(num == 0 || num == 1){
        matrix[i][j] = num;
      }
      else{
        cout << "The value must be 0 or 1, try again\n";
        j--;
      }
    }
  }
  return matrix;
}//end EnterMatrix

void PrintMatrix(vector<vector<int>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << "  ";
        }
        cout << "\n";
    }
}//end PrintMatrix

vector<vector<int>> SumRest(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, char operation){
    vector<vector<int>> matrixC(matrixA.size(), vector<int>(matrixA[0].size()));
    if (operation == '+'){
        for (int i = 0; i < matrixA.size(); i++){
            for (int j = 0; j < matrixA[0].size(); j++){
                matrixC[i][j] = (matrixA[i][j] + matrixB[i][j]);
            }
        }
    }
    else{
        for (int i = 0; i < matrixA.size(); i++){
            for (int j = 0; j < matrixA[0].size(); j++){
                matrixC[i][j] = (matrixA[i][j] - matrixB[i][j]);
            }
        }
    }
    return matrixC;
}//end SumRest

vector<vector<int>> ScalarMultiplication(vector<vector<int>>& matrix, int scalar){
    vector<vector<int>> matrixR(matrix.size(), vector<int>(matrix[0].size()));
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size(); j++){
            matrixR[i][j] = (scalar * matrix[i][j]);
        }
    }
    return matrixR;
}//end ScalarMultiplication

vector<vector<int>> MatrixMultiplication(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB){
    vector<vector<int>> matrixC(matrixA.size(), vector<int>(matrixB[0].size()));
    for (int i = 0; i < matrixA.size(); ++i) {
        for (int j = 0; j < matrixB[0].size(); ++j) {
            for (int k = 0; k < matrixA[0].size(); ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return matrixC;
}//end MatrixMultiplication

vector<vector<int>> MatrixTranspose(vector<vector<int>>& matrix){
    vector<vector<int>> matrixT(matrix[0].size(), vector<int>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size(); j++){
            matrixT[j][i] = matrix[i][j];
        }
    }
    return matrixT;
}//end MatrixTranspose

vector<vector<int>> GetSubMatrix(const vector<vector<int>>& matrix, int rowRemove, int columnRemove) {
    vector<vector<int>> subMatrix(matrix.size() - 1, vector<int>(matrix.size() - 1));
    int subRow = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        if (i != rowRemove) {
            int subCol = 0;
            for (int j = 0; j < matrix.size(); ++j) {
                if (j != columnRemove) {
                    subMatrix[subRow][subCol++] = matrix[i][j];
                }
            }
            ++subRow;
        }
    }

    return subMatrix;
}//end GetSubMatrix


int Determinant(vector<vector<int>>& matrix, int num) {
    if (num == 1) {
        return matrix[0][0];
    }
    if (num == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int detMatrix = 0;
    for (int x = 0; x < num; ++x) {
        vector<vector<int>> subMatrix = GetSubMatrix(matrix, 0, x);
        int subDetMatrix = Determinant(subMatrix, num - 1);
        detMatrix += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * subDetMatrix;
    }

    return detMatrix;
}//end Determinant

vector<vector<int>> AdjMatrix(const vector<vector<int>>& matrix) {
    vector<vector<int>> cofactorMatrix(matrix.size(), vector<int>(matrix.size()));

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            vector<vector<int>> subMatrix = GetSubMatrix(matrix, i, j);
            int subDetMatrix = Determinant(subMatrix, matrix.size() - 1);
            cofactorMatrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * subDetMatrix;
        }
    }

    return MatrixTranspose(cofactorMatrix); 
}//end AdjMatrix


vector<vector<double>> InverseMatrix(const vector<vector<int>>& matrix, int detMatrix) {

    if (detMatrix == 0) {
        cout << "La matriz no tiene inversa porque su determinante es cero.\n";
        return {};  // Retorna una matriz vacía
    }

    vector<vector<int>> adjMatrix = AdjMatrix(matrix);
    vector<vector<double>> inverseMatrix(adjMatrix.size(), vector<double>(adjMatrix.size()));

    for (int i = 0; i < adjMatrix.size(); ++i) {
        for (int j = 0; j < adjMatrix.size(); ++j) {
            inverseMatrix[i][j] = static_cast<double>(adjMatrix[i][j]) / detMatrix;
        }
    }

    return inverseMatrix;
}//end InverseMatrix


void Opcion1(){
    cout << "\nOperaciones: \n";
    cout << "(+) Suma \n";
    cout << "(-) Resta \n";

    cout << "Digite el simbolo de la operacion que desea realizar: ";
    char option;
    cin >> option;

    if (option == '+' || option == '-'){

        cout << "\nIngrese la matriz A:\n";
        vector<vector<int>> matrixA = EnterMatrix();
        cout << "\nIngrese la matriz B:\n";
        vector<vector<int>> matrixB = EnterMatrix();

        if(matrixA.size() == matrixB.size() && matrixA[0].size() == matrixB[0].size()){
            vector<vector<int>> matrixC = SumRest(matrixA, matrixB, option);
            cout << "La matriz resultante es: \n";
            PrintMatrix(matrixC);
        }
        else{
            cout << "Las matrices no son del mismo tamaño, intentelo de nuevo.\n";
            Opcion1();
        }
    }
    else{
        cout << "Opcion no valida, intentelo de nuevo.\n";
        Opcion1();
    }
}//end Option1

void Option2(){
    cout << "\nIngrese la matriz:\n";
    vector<vector<int>> matrix = EnterMatrix();
    cout << "Ingrese el escalar: ";
    int scalar;
    cin >> scalar;

    vector<vector<int>> matrixR = ScalarMultiplication(matrix, scalar);

    cout << "La matriz resultante es: \n";
    PrintMatrix(matrixR);
}//end Option2

void Option3(){
    cout << "\nIngrese la matriz A:\n";
    vector<vector<int>> matrixA = EnterMatrix();
    cout << "\nIngrese la matriz B:\n";
    vector<vector<int>> matrixB = EnterMatrix();

    if(matrixA[0].size() == matrixB.size()){
        vector<vector<int>> matrixC = MatrixMultiplication(matrixA, matrixB);
        cout << "La matriz resultante es: \n";
        PrintMatrix(matrixC);
    }
    else{
        cout << "Las columnas de la matriz A no es igual a las filas de la matriz B, intentelo de nuevo.\n";
        Option3();
    }
}//end Option3

void Option4(){
    cout << "\nIngrese la matriz:\n";
    vector<vector<int>> matrix = EnterMatrix();

    vector<vector<int>> matrixT = MatrixTranspose(matrix);
    cout << "La matriz Transpuesta es: \n";
    PrintMatrix(matrixT);
}//end Option4

void Option5(){
    cout << "\nIngrese la matriz:\n";
    vector<vector<int>> matrix = EnterMatrix();
    vector<vector<double>> inverseMatrix = InverseMatrix(matrix, Determinant(matrix, matrix.size()));

    if (!inverseMatrix.empty()) {
        cout << "La matriz inversa es:\n";
        //Mostrar la inversa
        for (int i = 0; i < inverseMatrix.size(); ++i){
            for (int j = 0; j < inverseMatrix[i].size(); ++j){
                cout << inverseMatrix[i][j] << "  ";
            }
            cout << "\n";
        }
    }
}//end Option5

void Option6(){
    cout << "\nIngrese la matriz:\n";
    vector<vector<int>> matrix = EnterMatrix();

    if (matrix.size() != matrix[0].size()) {
        cout << "La matriz debe ser cuadrada para calcular su determinante.\n";
    }
    else{

        int determinant = Determinant(matrix, matrix.size());
        cout << "El determinante de la matriz es: " << determinant;

    }

}//end Option6

int main(){
    cout << "Ejercicios con Matrices\n\n";
    cout << "Opciones:\n";
    cout << "0. Salir\n";
    cout << "1. Suma y Resta de Matrices.\n"; 
    cout << "2. Multiplicacion por un escalar.\n"; 
    cout << "3. Multiplicacion de Matrices.\n";
    cout << "4. Matriz Transpuesta.\n";
    cout << "5. Matriz Inversa.\n";
    cout << "6. Determinante de una Matriz.\n";

    cout << "Digite el numero de la opcion: ";
    unsigned int option;
    cin >> option;

    switch(option){
        case 0: return 0;
        case 1: Opcion1(); break;
        case 2: Option2(); break;
        case 3: Option3(); break;
        case 4: Option4(); break;
        case 5: Option5(); break;
        case 6: Option6(); break;
        default: cout << "Opción inválida. Intente de nuevo.";
    }
}