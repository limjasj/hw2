#include "movie.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating): 
  Product(category, name, price, qty),
  genre_(genre), rating_(rating)
{

}

/**
  * Returns the appropriate keywords that this product should be associated with
  */
std::set<std::string> Movie::keywords() const
{
  std::set<std::string> keyWords = parseStringToWords(name_);   //make title into separate words, put in new set
  keyWords.insert(convToLower(genre_));           //add genre to set
  keyWords.insert(convToLower(rating_));       //add rating to set

  return keyWords;    //return set
}

/**
  * Returns a string to display the product info for hits of the search
  */
std::string Movie::displayString() const
{
  std::string display= getName() + "\n" +
  "Genre: " + genre_ + " Rating: " + rating_ + "\n" +
  std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.\n";

  return display;
}

/**
  * Outputs the product info in the database format
  */
void Movie::dump(std::ostream& os) const
{
  Product::dump(os);  //dump for all product info
  os << genre_ << "\n" << rating_ << std::endl;  //dump for movie specific info
}