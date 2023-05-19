//Author: Camilla Calle 
//Date: March 19, 2023
//LibraryRecord.cpp
//In this file I implememnted a parameterized constructor that takes in the name of an input file (CSV file) as a string
//and the constructor reads the input file, where each line corresponds to a Book Subclass and dynamically alloted Book-derived 
//objects with the information read in from the input file this is then added to Library Record. In addition to this 
//I added helper functions to convert string into bool and enums, the displayFilter() function, and created pointers to Book.

#include "LibraryRecord.hpp"


/** default constructor**/
LibraryRecord::LibraryRecord() : ArrayBag<Book*>()
{
}

/*Parameterized Constructor*/

// Implement a parameterized constructor that takes the name of the input file as a reference to string argument. The constructor
//  will read the input file, where each line corresponds to a Book subclass 
// and dynamically allocate Book-derived objects with the information read from the input file and add them to the LibraryRecord.

LibraryRecord::LibraryRecord(const std::string& inputFile){ //Takes in what we need as string argumenet //We have to convert back 
  std::string title; std::string author; std::string page_count; std::string is_digital; std::string genre; 
  std::string subject; std::string grade_levels; std::string has_film_adaptation; std::string has_review_questions; 
  std::string device_model; std::string website; std::string book_type; std::string line; std::string temp; 
  std::ifstream helper;
  helper.open(inputFile, std::ios::in);
    if(!helper.is_open()){
      std::cout << "Failed to open!";
    }// Novel (represented by 1)// Textbook (represented by 2)// Manual (represented by 3)
        getline(helper,temp);
        while(getline(helper,line)){
            if(line.back()=='1'){
             std::stringstream s(line); getline(s,title,','); getline(s,author,',');
             getline(s,page_count,','); getline(s,is_digital,','); getline(s,genre,','); getline(s,subject,','); 
             getline(s,grade_levels,','); getline(s,has_film_adaptation,','); getline(s,has_review_questions,','); 
             getline(s,device_model,','); getline(s,website,','); getline(s,book_type); int updated_page_count = stoi(page_count); //string to int 
             bool upated_is_digital = convert_is_digitals(is_digital); bool updated_has_film_adptation = convert_is_digitals(has_film_adaptation);
             Book* check1 = new Novel(title, author, updated_page_count, genre, upated_is_digital, updated_has_film_adptation);
            checkIn(check1);
            } 
            //Textbook std::string name, std::string author, int page_count, std::string subject, bool is_digital = false, grade_level grade = NONE, bool has_review = false); 
            if(line.back()=='2'){std::stringstream s(line); getline(s,title,','); getline(s,author,',');
             getline(s,page_count,','); getline(s,is_digital,','); getline(s,genre,','); getline(s,subject,','); 
             getline(s,grade_levels,','); getline(s,has_film_adaptation,','); getline(s,has_review_questions,','); 
             getline(s,device_model,','); getline(s,website,','); getline(s,book_type);
             int updated_page_count = stoi(page_count); //string to int 
             bool updated_is_digital = convert_is_digitals(is_digital);/* bool updated_has_film_adptation = convert_is_digitals(has_film_adaptation);*/
             grade_level updated_grade_level = convert_grade_level(grade_levels); bool updated_review_questions = convert_is_digitals(has_review_questions);
             Book* check2 = new Textbook(title, author, updated_page_count, subject, updated_is_digital, updated_grade_level, updated_review_questions);
            checkIn(check2);
          }
            if(line.back()=='2'){
             std::stringstream s(line); getline(s,title,','); getline(s,author,',');
             getline(s,page_count,','); getline(s,is_digital,','); getline(s,genre,','); getline(s,subject,','); 
             getline(s,grade_levels,','); getline(s,has_film_adaptation,','); getline(s,has_review_questions,','); 
             getline(s,device_model,','); getline(s,website,','); getline(s,book_type); int updated_page_count = stoi(page_count); //string to int 
             bool updated_is_digital = convert_is_digitals(is_digital); /*bool updated_has_film_adptation = convert_is_digitals(has_film_adaptation);*/
             /*grade_level updated_grade_level = convert_grade_level(grade_levels);*//* bool updated_review_questions = convert_is_digitals(has_review_questions);*/
            //Manual(std::string name, std::string author, int page_count, std::string model, bool is_digital = false, std::string url = "", bool aid = false);
             Book* check3 = new Manual(title, author, updated_page_count, device_model, updated_is_digital, website, false);
             checkIn(check3);
            } 
  }
}

//Used helper function to convert strings to bool when needed.
bool LibraryRecord::convert_is_digitals(const std::string& updated_is_digital){
  if (updated_is_digital == "0") ///since this is a string it cant equal to another string
    return false;
  else
    return true;
}  

// // enum grade_level
// {
//   NONE,
//   ELEMENTARY,
//   JUNIOR_HIGH,
//   HIGH_SCHOOL,
//   COLLEGE
// };
//Helper function used to convert string to enum grade_level.
grade_level LibraryRecord::convert_grade_level(const std::string& updated_grade_level){
  
  if(updated_grade_level == "NONE") return NONE; 
  else if (updated_grade_level == "ELEMENTARY") 
  return ELEMENTARY;
  else if (updated_grade_level == "JUNIOR_HIGH") 
  return JUNIOR_HIGH;
  else if (updated_grade_level == "HIGH_SCHOOL") 
  return HIGH_SCHOOL;
  else if (updated_grade_level == "COLLEGE") 
  return COLLEGE;
  else 
  return COLLEGE;
}

/** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items, false otherwise
    @post:    adds book to items.
 **/
bool LibraryRecord::checkIn( Book* new_entry)
{
  bool has_room = (item_count_ < DEFAULT_CAPACITY);
  if (has_room)
  {
    items_[item_count_] = new_entry;
    item_count_++;
    return true;
  } // end if
  return false;
}

/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the check_out_history_ vector.
 **/
bool LibraryRecord::checkOut(Book* an_entry)
{
  int found_index = getIndexOf(an_entry);
  bool can_remove = !isEmpty() && (found_index > -1);
  if (can_remove)
  {
    item_count_--;
    items_[found_index] = items_[item_count_];
    check_out_history_.push_back(an_entry);
  }
  return can_remove;
}

/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out

      For each Book in the LibraryRecord you will output:
             [title_] is written by [author_]. Page Count: [page_count_]. [it is / is not] available digitally.\n
             It has been checked out [_] times.
**/
void LibraryRecord::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    int count = getCheckOutHistory(items_[i]);
    items_[i] ->display();
    std::cout << "It has been checked out " << count << " times." << std::endl;
  }
}

/**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles()
{
  for (int i = 0; i < item_count_; i++)
  {
    if (i < item_count_ - 1)
    {
      std::cout << items_[i] -> getTitle() << ", ";
    }
    else
    {
      std::cout << items_[i] -> getTitle() << "!\n";
    }
  }
}

/**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(Book* an_entry)
{
  int count = 0;

  for (int j = 0; j < check_out_history_.size(); j++)
  {
    if (check_out_history_[j] == an_entry)
    {
      count++;
    }
  }
  return count;
}

/** @param:   A reference to another ArrayBag object
      @post:    Combines the contents from both ArrayBag objects, EXCLUDING duplicates.
      Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

      IMPORTANT: We are carrying over the amount of times a book has been checked out.
      If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
      Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator/=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    if (contains(a_library_record.items_[index]))
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}

 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator+=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}
 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
std::vector<Book*> LibraryRecord::toVector()
{
  std::vector<Book*> bag_contents;
  for (int i = 0; i < item_count_; i++)
    bag_contents.push_back(items_[i]);

  return bag_contents;
}

/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock()
{
  if (item_count_ * 2 > DEFAULT_CAPACITY)
  {
    return false;
  }

  for (int i = 0; i < item_count_; i++)
  {
    items_[i + item_count_] = items_[i];
  }
  item_count_ = item_count_ * 2;
  return true;
}

/**
  @param:   A reference to a book
  @return: True or false depending on whether or not an item was removed
  @post: remove all elements of that book
*/
bool LibraryRecord::removeStock(Book* an_entry)
{
  bool res = false;
  while (contains(an_entry))
  {
    int found_index = getIndexOf(an_entry);
    item_count_--;
    for (int i = found_index; i < item_count_; i++)
    {
      items_[i] = items_[i + 1];
    }
    res = true;
  }
  return res;
}

/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the contents, regardless of their order. 
            For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
            and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
*/
bool LibraryRecord::equivalentRecords(LibraryRecord& a_library_record)
{
  bool result = true;

  //copy contents to count duplicates by marking them as empty
  // use copy because should not modify items_
  std::vector<Book*> library_copy = toVector();
  std::vector<Book*> other_copy = a_library_record.toVector();
  Book *empty; //not sure if i should do this

  for (int i = 0; i < library_copy.size(); i++)
  {
    for (int j = 0; j < other_copy.size(); j++)
    {
      if (other_copy[j] != empty && other_copy[j] == library_copy[i])
      {
        library_copy[i] = empty;
        other_copy[j] = empty;
      }
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < item_count_; i++)
  {
    if (library_copy[i] != empty)
    {
      result = false;
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < a_library_record.item_count_; i++)
  {
    if (other_copy[i] != empty)
    {
      result = false;
    }
  }
  return result;
}

// Implements LibraryRecord::displayFilter that takes a reference to 
// string key and displays information of its holdings whenever they key 
// matches the relevant information (specific to the type of book).
void LibraryRecord::displayFilter (const std::string& key) {
  for (int i = 0; i < getCurrentSize(); i++) {
    items_[i] -> displayFilter(key);
  }
}
