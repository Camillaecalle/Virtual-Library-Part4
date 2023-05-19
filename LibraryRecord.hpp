//Author: Camilla Calle 
//March 19, 2023
//LibraryRecord.hpp
//In this file I included headers and created pointers to Book.
#ifndef LIBRARY_RECORD_
#define LIBRARY_RECORD_

#include <sstream> 
#include <fstream>
#include "ArrayBag.hpp"
#include "Book.hpp"
#include <iostream>
#include "Manual.hpp"
#include "Novel.hpp"
#include "Textbook.hpp"


class LibraryRecord : public ArrayBag<Book*>{
  public:
    LibraryRecord(); //default constructor
    LibraryRecord(const std::string& inputFile);
    /** @param:   A reference to a Book object to be checked in
      @return:  returns true if a book was successfully added to items, false otherwise
      @post:    adds book to items.
    **/
	  bool checkIn(Book* new_entry);
    
    /** @param:   A reference to a Book object to be checked out   
        @return:  returns true if a book was successfully removed from items_, false otherwise
        @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the check_out_history_ vector.
    **/
	  bool checkOut(Book* an_entry);

    /**
      @param:   A reference to a Book object
      @return:  The number of times (int) the referenced Book has been checked out
    */
    int getCheckOutHistory(Book* an_entry);

    /**
      @return item_count_ : the current size of the bag
    **/

    
    std::vector<Book*> toVector();

    /**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out

        For each Book in the LibraryRecord you will output:
        [title_] is written by [author_]. Page Count: [page_count_]. [it is / is not] available digitally.\n
        It has been checked out [_] times.
    **/
   void display(); //Need to check 

    /**
      @post:    Prints the title of each Book in the LibraryRecord
      Example:
      "title1, title2, title3, title4!" Note the commas and exclamation mark.
    */  
    void displayTitles();

    /**
      @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
      @post:      Duplicates all the items in the LibraryRecord
      Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
    */
    bool duplicateStock();

    /**
      @param:   A reference to a book
      @return: True or false depending on whether or not an item was removed
      @post: remove all elements of that book
    */
    bool removeStock(Book* an_entry);

    /**
      @param:   A reference to another LibraryRecord
      @return:  Returns true if the 2 library records have the contents, regardless of their order. For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
      and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
    */
    bool equivalentRecords(LibraryRecord& a_library_record);

    /** @param:   A reference to another ArrayBag object
      @post:    Combines the contents from both ArrayBag objects, EXCLUDING duplicates.
      Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

      IMPORTANT: We are carrying over the amount of times a book has been checked out.
      If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
      Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
    void operator/=(LibraryRecord& a_library_record);

    /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
    void operator+=(LibraryRecord& a_library_record);
    
    // Implements LibraryRecord::displayFilter that takes a reference to string key 
    // and displays information of its holdings whenever they key matches the relevant 
    // information (specific to the type of book).
    void displayFilter (const std::string& key);
    
    bool convert_is_digitals(const std::string& test);
    grade_level convert_grade_level(const std::string& update_grade_level);
    
    protected:
   
    std::vector<Book*> check_out_history_; //a list of all the items that have been checked out

 
};
#endif
