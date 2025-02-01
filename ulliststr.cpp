#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) {
  // empty 
  if(head_ == NULL && tail_ == NULL) {
    Item* item = new Item();
    item->last = 1;
    item->val[0] = val;
    head_ = item;
    tail_ = item;

    size_ +=1;
  }
  else if(tail_->last == ARRSIZE) { // last item's array is full
    Item* item = new Item();
    item->last = 1;
    item->first = 0;
    item->val[0] = val;

    // update tail
    tail_->next = item;
    item->prev = tail_;
    tail_ = item;

    size_ +=1;
  } 
  else if( tail_->last != ARRSIZE){
    int lastIndex = tail_->last;
    tail_->val[lastIndex] = val;
    tail_->last += 1;
    size_ +=1;
  }
}

void ULListStr::push_front(const std::string& val){
  // empty 
  if(head_ == NULL && tail_ == NULL) {
    Item* item = new Item();
    // with push_front, adding to the end of array
    item->first = ARRSIZE -1;
    item->last = ARRSIZE;
    item->val[ARRSIZE-1] = val;
    head_ = item;
    tail_ = item;

    size_ +=1;
  }
  else if(head_->first == 0) { // first item's array is full
    Item* item = new Item();
    item->first = ARRSIZE-1;
    item->last = ARRSIZE;
    item->val[ARRSIZE-1] = val;

    // update tail
    head_->prev = item;
    item->next = head_;
    head_ = item;

    size_ +=1;
  } 
  else if( head_->first != 0){
    int firstIndex = head_->first;
    head_->val[firstIndex-1] = val; // add to previous index
    head_->first -= 1;
    size_ +=1;
  }
}

void ULListStr::pop_back(){
  if(tail_ == NULL){ // nothing to pop 
    return;
  }
  else if(tail_->last - tail_->first > 1) { // array has 1+ elements
    tail_->last -= 1;
    size_ -=1;
  }
  else if(tail_->last - tail_->first == 1) { // array has only 1 element; delete Item
    Item* del = tail_;
    tail_ = tail_->prev;
    if(tail_ == NULL) { // no Items remain
      head_ = NULL;
    }
    else if(tail_ != NULL){
      tail_->next = NULL;
    }
    delete del;
    size_ -=1; 
  }
}

void ULListStr::pop_front(){
  if(head_ == NULL){ // nothing to pop 
    return;
  }
  else if(head_->last - head_->first > 1 ) { // array has 1+ elements
    head_->first += 1;
    size_-=1;
  }
  else if(head_->last - head_->first == 1) { // array has only 1 element; delete Item
    Item* del = head_;
    head_ = head_->next;
    if(head_ == NULL){ // no Items remain
      tail_ = NULL;
    }
    else if(head_ != NULL){
      head_->prev = NULL;
    }
    delete del;
    size_ -=1;
  }
 
}

std::string const& ULListStr::back() const {
  int lastIndex = tail_->last;
  return tail_->val[lastIndex-1];
}

std::string const& ULListStr::front() const {
  int firstIndex  = head_->first;
  return head_->val[firstIndex];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  if(head_ == NULL){
    return NULL;
  }

  Item* temp = head_;
  while(temp != NULL){
    if(temp->last - temp->first > loc) { // number of elements in this item is greater than location index, loc in here
      return &(temp->val[temp->first + loc]);
    }
    loc = loc - (temp->last - temp->first); // decrement by number of elements in this item
    temp = temp->next; // go to next item;
    
  }

  return NULL; // loc not found
} 

void ULListStr::set(size_t loc, const std::string& val){
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
