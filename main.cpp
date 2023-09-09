// Project UID db1f506d06d84ab787baf250c265e24e

#include "csvstream.h"
#include <fstream>
#include <utility>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Classifier{
    public:
    struct Post{
        string label;
        string content;
        map<string, int> wordslist;
    };

    vector<Post> postslist;
    vector<Post> testslist;
    map<string, int> containword;
    map<string, int> containlabel;
    map<pair<string, string>, int> containboth;

    bool make(string traininput, string testinput){
        try {
            csvstream csvin1(traininput);
            }
        catch(const csvstream_exception &e) {
            cout << "Error opening file: " << traininput << endl;
            return false;
        }

        csvstream csvin1(traininput);
        map<string, string> row1;

        while (csvin1 >> row1) {
        Post post;
        post.label = row1["tag"];
        post.content = row1["content"];
        containlabel[post.label]++;
        stringstream source(post.content);
        string word;
        while (source >> word) {
          post.wordslist[word]++;
          if(post.wordslist[word] == 1){
               containword[word]++;
               containboth[{post.label, word}]++;
          }
         }    
         postslist.push_back(post);
        }

        try {
            csvstream csvin2(testinput);
            }
        catch(const csvstream_exception &e) {
            cout << "Error opening file: " << testinput << endl;
            return false;
        }

        csvstream csvin2(testinput);
        map<string, string> row2;

        while (csvin2 >> row2) {
        Post post;
        post.label = row2["tag"];
        post.content = row2["content"];
        stringstream source(post.content);
        string word;
        while (source >> word) {
            post.wordslist[word]++;
        }    
        testslist.push_back(post);
        }
        return true;
    }

    float calcprior(const string label){
    return log(((float) containlabel[label])/((float) postslist.size()));
    }

    float calclike(pair<string,string> pair){
        if(containboth.find(pair) != containboth.end() 
        && containboth.find(pair)->second > 0){
          return log(( (float) containboth[pair])/
          ((float) containlabel[pair.first]));
        }
        else if(containword.find(pair.second) != containword.end()
        && containword.find(pair.second)->second > 0){
          return log(( (float) containword[pair.second])/
          ( (float) postslist.size()));
        }
        else{
          return log(((float) 1)/( (float) postslist.size()));
        }
    }

    pair<string, float> predict(Post p){
        pair<string, float> max = {"", 0};
        for(auto i = containlabel.begin(); i != containlabel.end(); ++i){
            float prior = calcprior(i->first);
            float total = 0;
            for(auto i2 = p.wordslist.begin(); i2 != 
              p.wordslist.end(); ++i2){
              total += calclike({i->first, i2->first});
            }
            if(total + prior > max.second || max.first == ""){
                max.first = i->first;
                max.second = total + prior;
            }
        }
        return max;
    }
};

bool errorcheck(bool &debug, int argc, char *argv[]){
    if(argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return true;
    }
    if(argc == 4){
        string s = argv[3];
        if(s == "--debug"){
            debug = true;
            return false;
        }
        else{
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return true;;
        }
    }
    else{
        debug = false;
        return false;
    }
}

void main_helper1(bool debug, Classifier classifier){
    if(debug){
        cout << "training data:" << endl;
        for(auto i = classifier.postslist.begin(); 
        i != classifier.postslist.end(); ++i){
            cout << "  label = " << i->label 
            << ", content = " << i->content 
            << endl;
        }
    }
    cout << "trained on " << classifier.postslist.size()
    << " examples" << endl;
    if(debug){
        cout << "vocabulary size = " << classifier.containword.size()
        << endl;
    cout << endl;
    cout << "classes:" << endl;
    }
}

void main_helper2(bool debug, Classifier classifier){
    if(debug){
    for(auto i = classifier.containlabel.begin(); 
    i != classifier.containlabel.end(); ++i){
         cout << "  " << i->first << ", " 
         << i->second << " examples, log-prior = "
         << classifier.calcprior(i->first) << endl;
    }
    cout << "classifier parameters:" << endl;
    for(auto i = classifier.containboth.begin();
    i != classifier.containboth.end(); ++i){
        cout << "  " << i->first.first << ":" << i->first.second
        << ", count = " << i->second << ", log-likelihood = "
        << classifier.calclike(i->first) << endl;
    }
    }
    cout << endl;
    cout << "test data:" << endl;
}

void main_helper3(bool debug, Classifier classifier, int correct){
    for(auto i = classifier.testslist.begin(); 
    i != classifier.testslist.end(); ++i){
        pair<string, float> guess = classifier.predict(*i);
        cout << "  correct = " << i->label <<  
        ", predicted = " << guess.first <<  
        ", log-probability score = " << guess.second 
        << endl;
        cout << "  content = " << i->content << endl << endl;
        if(guess.first == i->label){
            correct++;
        }
    }
    cout << "performance: " << correct << " / "
    << classifier.testslist.size() 
    << " posts predicted correctly" << endl;
}

int main(int argc, char *argv[]){
    bool debug = false;
    if(errorcheck(debug, argc, argv)){
        return 1;
    };
    cout.precision(3);
    string training = argv[1];
    string testing = argv[2];
    Classifier classifier;
    int correct = 0;
    if(!classifier.make(training, testing)){
        cout << "Error opening file: " << argv[0] << endl;
        return 1;
    }
    main_helper1(debug, classifier);
    main_helper2(debug, classifier);
    main_helper3(debug, classifier, correct);
}