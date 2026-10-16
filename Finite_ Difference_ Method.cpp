//Qn : y"=-2  ,y(0)=0  ,y(1)=0
//coefficients :
// Ai=1-hPi/2
// Bi=-2+h^2*Qi
// Ci=1+h*Pi/2
// Di=h^2*Ri
//CODE:
#include <iostream>
#include <vector>
using namespace std;
double P(double x){
	return 0.0;
}
double Q(double x){
	return 0.0;
}
double R(double x){
	return -2;
}
int main(){
	
    double x_left = 0.0; // Starting x
    double x_right = 1.0; // Ending x
    double alpha = 0.0;   // Starting y ki value y(0)
    double beta = 0.0;    // Ending y ki value y(1)
    
    int n;
    cout << "Enter number of subintervals n: ";
    cin >> n;
    
    if (n < 2) {
        cout << "Number of subintervals must be at least 2." << endl;
        return 0;
    }
    double h = (x_right - x_left) / n; // Step size
    int m = n - 1; // Number of interior unknowns
    vector<double> A(m);
    vector<double> B(m);
    vector<double> C(m);
    vector<double> D(m);
    //Vector isliye liya kyunki m ka size user ke
	// input par depend karta hai (dynamic memory).
	// For loop for finite difference equations
    for (int j = 0; j < m; j++) {
        int i = j + 1; // Interior grid index
        
        //C++ mein arrays aur vectors ki indexing hamesha 0 se shuru hoti hai.
        //agar loop 1 se suru kare toh A[1] se data bharna suru hota aur A[0] main garbage value ajataa!
        //matrix ka size eqn par depend nhi krta ! no of intervals par krta hai!
        double x = x_left + i * h; // Current x ki position nikal raha hai
        
        double Pi = P(x); // Current x par P(x)
        double Qi = Q(x);// Current x par Q(x)
        double Ri = R(x);// Current x par R(x)
        
        // Equations bana raha hai
        A[j] = 1.0 - h * Pi / 2.0;
        B[j] = -2.0 + h * h * Qi; 
        C[j] = 1.0 + h * Pi / 2.0; 
        D[j] = h * h * Ri;}
        //A_0 y_0 + B_0 y_1 + C_0 y_2 = D_0
        // Boundary conditions apply kar rahe hain
    D[0] = D[0] - A[0] * alpha;
    D[m - 1] = D[m - 1] - C[m - 1] * beta;
    
    A[0] = 0.0;
    C[m - 1] = 0.0;
    
        
    // ---------------- Thomas Algorithm shuru ---------------- 
    
    // Naya vector banaya final answers (y values) store karne ke liye
    vector<double> y(m); 
    
    // Step 1: Forward Elimination
    for (int j = 1; j < m; j++) {
        // Ek factor nikalte hain jisse pichli row ko multiply karke isme minus karenge
        double factor = A[j] / B[j - 1]; 
        
        // B aur D modify ho jate hain, A effectively zero ho jata hai (hum use store nahi karte zero karke)
        B[j] = B[j] - factor * C[j - 1]; 
        D[j] = D[j] - factor * D[j - 1]; 
    }
    // Step 2: Backward Substitution
    // Sabse aakhri value toh direct nikal aayegi
    y[m - 1] = D[m - 1] / B[m - 1];
    
    // Ab aakhri se 2nd last, 3rd last... uper ki taraf jayenge
    for (int j = m - 2; j >= 0; j--) {
        // Current 'y' nikalne ke liye aage wali known 'y' value (y[j+1]) ka use karenge
        y[j] = (D[j] - C[j] * y[j + 1]) / B[j];
    }
    // Final Result print karna
    cout << "\nResults (Interior points):" << endl;
    for(int j = 0; j < m; j++) {
        double current_x = x_left + (j + 1) * h;
        cout << "x = " << current_x << " \t y = " << y[j] << endl;
    }

    return 0;
}
