#include "book.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author): 
  Product(category, name, price, qty),
  isbn_(isbn), author_(author)
{

}

/**
  * Returns the appropriate keywords that this product should be associated with
  */
std::set<std::string> Book::keywords() const
{
  std::set<std::string> keyWords= parseStringToWords(name_);   //make title into separate words, put in new set
  std::set<std::string> authorName= parseStringToWords(author_);
  for(std::set<std::string>::iterator it=authorName.begin(); it != authorName.end(); ++it)
  {
    keyWords.insert(*it);
  }
  keyWords.insert(isbn_);  //add isbn to set

  return keyWords;    //return set
}

/**
  * Returns a string to display the product info for hits of the search
  */
std::string Book::displayString() const
{
  std::string display= getName() + "\n" +
  "Author: " + author_ + " ISBN: " + isbn_ + "\n" +
  std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.\n";

  return display;
}

/**
  * Outputs the product info in the database format
  */
void Book::dump(std::ostream& os) const
{
  Product::dump(os);
  os << isbn_ << "\n" << author_ << std::endl;
}