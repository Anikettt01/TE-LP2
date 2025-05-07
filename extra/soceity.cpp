#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, string> facts;

void acquire_knowledge() {
    string input;

    cout << "=== Knowledge Acquisition ===\n";

    cout << "Was there pump maintenance on Monday? (yes/no): ";
    cin >> input;
    facts["pump_maintenance_monday"] = input;

    cout << "Was there power outage on Monday? (yes/no): ";
    cin >> input;
    facts["power_outage_monday"] = input;

    cout << "Was there power outage in passage today? (yes/no): ";
    cin >> input;
    facts["power_outage_passage"] = input;

    cout << "Are passage lights under repair? (yes/no): ";
    cin >> input;
    facts["passage_lights_repair"] = input;
}

void infer_water_supply_issue() {
    cout << "\n[a] Why was there no water supply on Monday?\n";

    if (facts["pump_maintenance_monday"] == "yes") {
        cout << "→ Water supply was off due to scheduled pump maintenance on Monday.\n";
    } else if (facts["power_outage_monday"] == "yes") {
        cout << "→ Water supply was unavailable because of a power outage affecting pumps on Monday.\n";
    } else {
        cout << "→ No specific reason recorded for water supply issue on Monday.\n";
    }
}

void infer_passage_light_issue() {
    cout << "\n[b] Why were there no lights in the common passage?\n";

    if (facts["power_outage_passage"] == "yes") {
        cout << "→ Lights were off due to a power outage in the passage area.\n";
    } else if (facts["passage_lights_repair"] == "yes") {
        cout << "→ Passage lights were turned off for repair/maintenance work.\n";
    } else {
        cout << "→ No specific reason recorded for lights being off in the common passage.\n";
    }
}

int main() {
    acquire_knowledge();
    infer_water_supply_issue();
    infer_passage_light_issue();

    return 0;
}
