/*______ _                     _     _           _ 
 |  ____| |              /\   | |   (_)         | |
 | |__  | |  ______     /  \  | |__  _  __ _  __| |
 |  __| | | |______|   / /\ \ | '_ \| |/ _` |/ _` |
 | |____| |           / ____ \| |_) | | (_| | (_| |
 |______|_|          /_/    \_\_.__/|_|\__,_|\__,_|
*/     

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <limits>
using namespace std;

// Utility to pause the screen until user presses Enter
#define wait cout << "\nPress Enter to return to menu..."; \
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); \
             cin.get();

// Divider for UI formatting
const string divider = string(35, '-');

// Function prototypes
void Add_a_language();
void Remove_a_language();
void Display_my_languages();
void Display_insights();

// Language structure to hold language information
struct Language {
    string name;
    bool known; // whether the user knows this language
    int nativeSpeakersMillions;
    vector<string> countriesSpoken;
};

// Initial list of languages with their stats and where they are spoken
vector<Language> languages = {
    {"Arabic", false, 310, {
        "Algeria", "Bahrain", "Chad", "Comoros", "Djibouti", "Egypt",
        "Eritrea", "Iraq", "Jordan", "Kuwait", "Lebanon", "Libya",
        "Mauritania", "Morocco", "Oman", "Palestine", "Qatar",
        "Saudi Arabia", "Somalia", "Sudan", "Syria", "Tunisia",
        "UAE"
    }},
    {"Chinese", false, 920, {
        "China", "Taiwan", "Singapore", "Malaysia"
    }},
    {"English", false, 380, {
        "Antigua and Barbuda", "Australia", "Bahamas", "Barbados", "Belize",
        "Botswana", "Cameroon", "Canada", "Dominica",
        "Eswatini", "Fiji", "Gambia", "Ghana", "Grenada",
        "Guyana", "Ireland", "Jamaica", "Kenya", "Lesotho",
        "Malta", "Micronesia", "Namibia", "Nauru", "New Zealand",
        "Nigeria", "Pakistan", "Palau", "Papua New Guinea", "Philippines",
        "Rwanda", "Saint Kitts and Nevis", "Saint Lucia",
        "Saint Vincent and the Grenadines", "Samoa", "Sierra Leone",
        "Solomon Islands", "South Africa", "South Sudan",
        "Tanzania", "Trinidad and Tobago", "Uganda", "UK", "USA",
        "Vanuatu", "Zambia", "Zimbabwe"
    }},
    {"French", false, 80, {
        "Belgium", "Benin", "Burkina Faso", "Burundi", "Cameroon",
        "Canada", "Central African Republic", "Chad", "Comoros",
        "Congo (Brazzaville)", "Congo (Kinshasa)", "Djibouti",
        "Equatorial Guinea", "France", "Gabon", "Guinea", "Haiti",
        "Ivory Coast", "Luxembourg", "Madagascar", "Mali", "Monaco",
        "Niger", "Rwanda", "Senegal", "Seychelles", "Switzerland",
        "Togo", "Vanuatu"
    }},
    {"German", false, 95, {
        "Austria", "Belgium", "Germany", "Liechtenstein", "Luxembourg"
    }},
    {"Japanese", false, 125, {
        "Japan"
    }},
    {"Russian", false, 150, {
        "Belarus", "Kazakhstan", "Kyrgyzstan", "Russia"
    }},
    {"Spanish", false, 475, {
        "Argentina", "Bolivia", "Chile", "Colombia", "Costa Rica",
        "Cuba", "Dominican Republic", "Ecuador", "El Salvador",
        "Equatorial Guinea", "Guatemala", "Honduras", "Mexico",
        "Nicaragua", "Panama", "Paraguay", "Peru", "Spain", "Uruguay", "Venezuela"
    }}
};

int main() {
    cout << "Welcome to the language helper\n";
    int choice = -1;

    // Main menu loop
    do {
        cout << divider
             << '\n'
             << "-- Main menu --"
             << "\n1)Add a language"
             << "\n2)Remove a language"
             << "\n3)Display my languages"
             << "\n4)Display insights"
             << "\n0)Exit\n"
             << "Enter a number: ";
        cin >> choice;

        // Handle user choice
        switch (choice) {
        case 1:
            Add_a_language(); break;
        case 2:
            Remove_a_language(); break;
        case 3:
            Display_my_languages(); break;
        case 4:
            Display_insights(); break;
        case 0:
            cout << "Goodbye!......\n"; break;
        default:
            // Invalid input handling
            cout << divider
                 << '\n'
                 << "Invalid input. Please enter a number from the list.\n"
                 << divider;
            wait;
            break;
        }
    } while (choice != 0);
    return 0;
}

// Function to mark a language as known
void Add_a_language() {
    int cnt = 1;
    vector<int> availableIndices;

    // List only unknown languages
    for (int i = 0; i < languages.size(); ++i) {
        if (!languages[i].known) {
            cout << cnt << ") " << languages[i].name << '\n';
            availableIndices.push_back(i);
            cnt++;
        }
    }

    if (availableIndices.empty()) {
        cout << divider
             << '\n'
             << "You've already marked all languages as known.\n"
             << divider;
        wait;
        return;
    }

    // Prompt for user input
    cout << divider << '\n';
    cout << "Choose a language to mark as known\n";
    cout << divider << '\n';
    cout << "Enter a number to mark that language as known: ";
    int choice;
    cin >> choice;

    // Validate input
    while (cin.fail() || choice < 1 || choice > availableIndices.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
        cin >> choice;
    }

    // Mark language as known
    int realIndex = availableIndices[choice - 1];
    languages[realIndex].known = true;
    cout << divider
         << '\n'
         << languages[realIndex].name << " marked as known!\n"
         << divider;
    wait;
}

// Function to unmark a known language
void Remove_a_language() {
    cout << divider << '\n';
    int cnt = 1;
    vector<int> availableIndices;

    // List only known languages
    for (int i = 0; i < languages.size(); ++i) {
        if (languages[i].known) {
            cout << cnt << ") " << languages[i].name << '\n';
            availableIndices.push_back(i);
            cnt++;
        }
    }

    if (availableIndices.empty()) {
        cout << "-- You haven't added any languages yet --";
        wait;
        return;
    }

    // Prompt user for which language to remove
    cout << "Enter a number to mark that language as unknown: ";
    int choice;
    cin >> choice;

    // Validate input
    while (cin.fail() || choice < 1 || choice > availableIndices.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
        cin >> choice;
    }

    // Unmark language
    int realIndex = availableIndices[choice - 1];
    languages[realIndex].known = false;
    cout << divider
         << '\n'
         << languages[realIndex].name << " marked as unknown!\n"
         << divider;
    wait;
}

// Function to display all known languages
void Display_my_languages() {
    cout << divider << '\n';

    bool empty = true;
    int cnt = 1;

    for (int i = 0; i < languages.size(); ++i) {
        if (languages[i].known) {
            if (empty) {
                cout << "Your known languages:\n\n";
                empty = false;
            }
            cout << cnt << ") " << languages[i].name << '\n';
            cnt++;
        }   
    }

    if (empty) {
       cout << "-- You haven't added any languages yet --";
    }
    wait;
}

// Function to display insights: total native speakers & number of countries
void Display_insights() {
    cout << divider << '\n';
    
    int totalNativeSpeakers = 0;
    int total_languages = 0;
    unordered_set<string> uniqueCountries;

    // Count native speakers and unique countries from known languages
    for (const auto& lang : languages) {
        if (lang.known) {
            total_languages++;
            totalNativeSpeakers += lang.nativeSpeakersMillions;
            for (const auto& country : lang.countriesSpoken) {
                uniqueCountries.insert(country);
            }
        }
    }

    if (totalNativeSpeakers == 0) {
        cout << "-- You haven't added any languages yet --";
        wait;
        return;
    }

    // Display insights
    cout << "-- Language Insights --\n\n";
    cout << "You speak " << total_languages << " language(s)!\n";
    for (const auto& lang : languages) {
        if (lang.known) {
            cout << lang.name << ' ';
        }
    }
    if (totalNativeSpeakers < 1000)
        cout << "\nTotal native speakers: " << totalNativeSpeakers << " million\n";
    else
        cout << "\nTotal native speakers: " << totalNativeSpeakers / 1000.0 << " billion\n";

    cout << "Total countries you can visit (official language): " << uniqueCountries.size() << "\n";
    cout << divider;
    wait;
}
