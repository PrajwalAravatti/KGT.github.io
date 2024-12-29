#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include<vector>
using namespace std;

class recommendation_data
{
private:
    char movie_name[150][30];
    char recommendation_name[150][30];
    int viewers[150];
    int global_count;

public:
    recommendation_data();

    void welcome();
    void load_from_file();
    void display_data();
    void string_search(string name);
};


recommendation_data::recommendation_data()
{
    global_count = 0;
}


void recommendation_data::welcome()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tRECOMMENDATION ENGINE\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void recommendation_data::load_from_file()
{
    ifstream file("C:\\Users\\DELL\\Downloads\\MovieIndex.txt");

    if (!file)
    {
        cout << "File Not Found\n";
        return;
    }

    while (file >> movie_name[global_count]
                >> recommendation_name[global_count]
                >> viewers[global_count])
    {
        if (global_count < 150)
            global_count++;
        else
        {
            cout << "Maximum data limit reached.\n";
            break;
        }
    }

    file.close();
}

void recommendation_data::display_data()
{
    for (int i = 0; i < global_count; i++)
    {
        cout << setw(30) << movie_name[i]
             << setw(30) << recommendation_name[i]
             << setw(10) << viewers[i] << endl;
    }
}

void recommendation_data::string_search(string name) {
    vector<pair<string, int> > recommendations;

    for (int i = 0; i < global_count; i++) {
        bool f = true;
        for (int j = 0; j < name.length() && f; j++) {
            if (movie_name[i][j] != name[j]) {
                f = false;
            }
        }

        if (f) {
            cout << "Movie found: " << movie_name[i] << endl;
            recommendations.push_back(make_pair(recommendation_name[i], viewers[i]));
        }
    }


    for (size_t i = 0; i < recommendations.size(); i++) {
        cout << "Recommendation: " << recommendations[i].first << " (Viewers: " << recommendations[i].second << ")" << endl;

    }
    for (int i = 1; i < recommendations.size(); i++) {
        pair<string, int> v= recommendations[i];
        int j = i - 1;

        while (j >= 0 && recommendations[j].second < v.second) {
            recommendations[j + 1] = recommendations[j];
            j = j - 1;
        }
        recommendations[j + 1] = v;
    }

    //
    for (size_t i = 0; i < recommendations.size(); i++) {
        cout << "Recommendation: " << recommendations[i].first << " (Viewers: " << recommendations[i].second << ")" << endl;
    }
}

int main()
{
    recommendation_data engine;
    engine.welcome();

    engine.load_from_file();
    engine.display_data();
    string name;
    cout<<"enter the string"<<endl;
    cin>>name;
    engine.string_search(name);


    // TO-DO: add the remaining

    return 0;
}


