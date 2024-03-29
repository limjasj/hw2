#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);
void displayProducts2(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    //DataStore ds;
    MyDataStore ds;


    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line); //line(input) is in stringstream ss
        string cmd;
        if((ss >> cmd)) //takes out first work and allows us to see what it is
        { 
          if( cmd == "AND") {
              string term;
              vector<string> terms;
              while(ss >> term) {
                  term = convToLower(term);
                  terms.push_back(term);
              }
              hits = ds.search(terms, 0);
              displayProducts(hits);
          }
          else if ( cmd == "OR" ) {
              string term;
              vector<string> terms;
              while(ss >> term) {
                  term = convToLower(term);
                  terms.push_back(term);
              }
              hits = ds.search(terms, 1);
              displayProducts(hits);
          }
          else if ( cmd == "QUIT") {
              string filename;
              if(ss >> filename) {
                  ofstream ofile(filename.c_str());
                  ds.dump(ofile);
                  ofile.close();
              }
              done = true;
          }
          /* Add support for other commands here */
          else if ( cmd == "ADD")
          {
            //must add the index from hits to the cart
            Product* indexProduct;
            unsigned int index;
            std::string username;
            if((ss >> username) && (ss >> index)) //read the int and User* from ss
            {
              if(ds.userExists(username)) //check if user exists
              {
                if((index<0) || (index > hits.size()))  //index is more than size, <0
                {
                  cout << "Invalid request" << endl;
                }
                else
                {
                  indexProduct=hits[index-1]; //pass in the product from hits
                  ds.addToCart(username, indexProduct); //use function from myDataStore
                }
              }
              else
              {
                cout<<"Invalid request \n";
              }
            }
            else
            {
              cout << "Invalid request" << endl;
            }
          }
          else if ( cmd == "VIEWCART") //string to pass into function
          {
            std::string username;  //create a string to pass into function
            if(ss >> username) //read in the string 
            {
              if(ds.userExists(username)) //check if user exists
              {
                std::vector<Product*> displayVector = ds.viewCart(username); //call viewCart function
                displayProducts2(displayVector);
              }
              else
              {
                cout<<"Invalid Username \n";
              }
            }
            else
            {
              cout << "Invalid username" << endl;
            }
          }
          else if ( cmd == "BUYCART")
          {
            string username;  //create a string to pass into function
            if(ss >> username) //read in the string
            {
              if(ds.userExists(username)) //check if user exists
              {
                ds.buyCart(username); //call buyCart function
              }
              else
              {
                cout<<"Invalid Username \n";
              }
            }
            else
            {
              cout << "Invalid username" << endl;
            }
          }
          else 
          {
              cout << "Unknown command" << endl;
          }
        }
      else 
      {
          cout << "Unknown command" << endl;
      }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

void displayProducts2(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Item " << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
