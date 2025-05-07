#include<bits/stdc++.h>
using namespace std;

double bmiCalculator(double heightCM, double weight){
    double heightM = heightCM/100.0;
    double bmi = weight/(heightM*heightM);
    return round(bmi*10.0)/10.0;
}

string calculate(double fasting, double postmeal,string &history, unordered_map<string,string>&mp){
    int score=0;
    if(fasting>=126) score+=2;
    if(postmeal>=200) score+=2;
    if(history=="yes") score+=1;
    int count=0;
    for(auto i:mp){
        if(i.second=="yes") count++;
    }
    if(count>0) score+=1;
    if(score>=4) return "High";
    else if(score>=2) return "Moderate";
    else return "Low";
}

bool evaluateDiabetes(double fasting, double postmeal,string &history, unordered_map<string,string>&mp){
    string riskLevel = calculate(fasting,postmeal,history,mp);
    cout<<"Diabetes risk level: "<<riskLevel<<" "<<endl;
    int count=0;
    for(auto i:mp){
        if(i.second=="yes") count++;
    }
    bool diabetesRisk = false;
    if(fasting>=126 || postmeal >= 200){
        diabetesRisk = true;
        cout<<"You are likely diabetic patient"<<endl;
        if (history == "yes") cout << "Note: History of diabetes present. Levels are critically high." << endl;
        else cout << "Warning: Diabetic levels detected with no prior history." << endl;
        cout << "Suggestion: Consult a diabetologist. Begin sugar control therapy.\n" << endl;
    }
    else if ((100 <= fasting && fasting < 126) || (140 <= postmeal && postmeal < 200)) {
        diabetesRisk = true;
        cout << "Diagnosis: Pre-diabetic stage." << endl;
        cout << "Suggestion: Control diet, exercise, and monitor monthly.\n" << endl;
    }
    else if (count > 0 && (fasting > 110 || postmeal > 160)) {
        diabetesRisk = true;
        cout << "Diagnosis: Symptoms with elevated sugar levels suggest early diabetes." << endl;
        cout << "Suggestion: Perform HbA1c test. Visit a physician.\n" << endl;
    }
    else cout << "Blood sugar levels are within safe range.\n" << endl;
    return diabetesRisk;
}

bool evaluateHypertension(int sys, int dia,  unordered_map<string, string>& symptoms) {
    bool hypertensionRisk = false;
    if (sys >= 140 || dia >= 90) {
        hypertensionRisk = true;
        cout << "🩺 Diagnosis: You have Hypertension (High BP)." << endl;
        if (symptoms.at("chest_pain") == "yes") {
            cout << "⚠️  Chest pain reported. Seek medical attention." << endl;
        }
        if (symptoms.at("headache") == "yes") {
            cout << "⚠️  Frequent headaches indicate vascular stress." << endl;
        }
        cout << "📝 Suggestion: Reduce salt intake, check BP regularly, consult cardiologist.\n" << endl;
    }
    else if ((120 <= sys && sys < 140) || (80 <= dia && dia < 90)) {
        hypertensionRisk = true;
        cout << "🩺 Diagnosis: Pre-hypertension stage." << endl;
        cout << "📝 Suggestion: Manage with lifestyle changes. Monitor BP closely.\n" << endl;
    }
    else {
        cout << "✅ Blood pressure is within normal range.\n" << endl;
    }
    return hypertensionRisk;
}

bool generalSymptomCheck(bool diabetesRisk, bool hypertensionRisk,  unordered_map<string, string>& symptoms) {
    bool mildWarning = false;
    if (symptoms.at("frequent_thirst") == "yes" || symptoms.at("frequent_urination") == "yes" ||
        symptoms.at("blurred_vision") == "yes" || symptoms.at("fatigue") == "yes") {
        mildWarning = true;
        cout << "⚠️  Mild symptoms detected despite normal readings." << endl;
        cout << "📝 Suggestion: Repeat tests in 2 weeks. Monitor your condition.\n" << endl;
    }
    else if (symptoms.at("chest_pain") == "yes" || symptoms.at("headache") == "yes") {
        mildWarning = true;
        cout << "⚠️  Chest pain/headache detected without hypertension." << endl;
        cout << "📝 Suggestion: Could be stress-related. Consider ECG or doctor visit.\n" << endl;
    }
    else cout << "You have no mild symptoms. That's great!" << endl;
    return mildWarning;
}

void finalSummary(int age, bool diabetesRisk, bool hypertensionRisk, bool mildWarning) {
    if (!diabetesRisk && !hypertensionRisk && !mildWarning) {
        cout << "✅ You are in good health based on provided inputs." << endl;
        if (age > 45) cout << "🔄 Age over 45: Regular checkups are advised.\n" << endl;
        else cout << "💪 Keep up the healthy lifestyle!\n" << endl;
    }
}


int main(){
    int age;
    double height,weight;
    cout<<"Enter the age: ";
    cin>>age;
    cout<<"Enter height: ";
    cin>>height;
    cout<<"Enter weight: ";
    cin>>weight;
    double bmi = bmiCalculator(height,weight);
    cout<<"Your bmi is: "<<bmi<<" - ";
    if(bmi<18.5) cout<<"UnderWeight";
    else if(bmi>=18.5 && bmi<=24.9) cout<<"Normal(Good)"<<endl;
    else if(bmi>=25 && bmi < 29.9) cout<<"Overweight"<<endl;
    else cout<<"Obese"<<endl;
    cout<<endl;
    double sugarBefore,sugarAfter;
    int upperBP,lowerBP;
    cout << "Enter fasting blood sugar level (mg/dL): ";
    cin >>sugarBefore;
    cout << "Enter post-meal blood sugar level (mg/dL): ";
    cin >>sugarAfter;
    cout << "Enter systolic BP (upper number): ";
    cin >>upperBP;
    cout << "Enter diastolic BP (lower number): ";
    cin >>lowerBP;
    string historyDiabetes;
    cout<<"Do you have a history of diabetes? (yes/no): ";
    cin>>historyDiabetes;
    unordered_map<string,string>mp;
    cout << "Do you often feel thirsty? (yes/no): ";
    cin >> mp["frequent_thirst"];
    cout << "Do you urinate frequently? (yes/no): ";
    cin >> mp["frequent_urination"];
    cout << "Do you have blurred vision? (yes/no): ";
    cin >> mp["blurred_vision"];
    cout << "Do you feel tired often? (yes/no): ";
    cin >> mp["fatigue"];
    cout << "Do you experience chest pain? (yes/no): ";
    cin >> mp["chest_pain"];
    cout << "Do you experience frequent headaches? (yes/no): ";
    cin >> mp["headache"];
    cout<<"-----------REPORT------------";
    bool diatebesRisk = evaluateDiabetes(sugarBefore,sugarAfter,historyDiabetes,mp);
    bool hypertension = evaluateHypertension(upperBP,lowerBP,mp);
    bool mildWarning = generalSymptomCheck(diatebesRisk,hypertension,mp);

    finalSummary(age,diatebesRisk,hypertension,mildWarning);
    return 0;
}