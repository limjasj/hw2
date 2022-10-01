#include "clothing.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand): 
  size_(size), brand_(brand),
  Product(category, name, price, qty)
{

}

/**
  * Returns the appropriate keywords that this product should be associated with
  */
std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> keyWords = parseStringToWords(name_);   //make title into separate words, put in new set
  keyWords.insert(size_);           //add size to set
  std::set<std::string> brandName = parseStringToWords(brand_);   //create set brandName, make it have brand words
  for(std::set<std::string>::iterator it=brandName.begin(); it != brandName.end(); ++it) //iterate through brandName
  {
    keyWords.insert(*it); //add brand word into keyWords
  }

  return keyWords;    //return set
}

/**
  * Returns a string to display the product info for hits of the search
  */
std::string Clothing::displayString() const
{
  std::string display= getName() + "\n" +
  "Size: " + size_ + " Brand: " + brand_ + "\n" +
  std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.\n";

  return display;
}

/**
  * Outputs the product info in the database format
  */
void Clothing::dump(std::ostream& os) const
{
  Product::dump(os);  //dump for all product info
  os << size_ << "\n" << brand_ << std::endl;  //dump for clothing specific info
}