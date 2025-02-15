#include "TaxonSet.hpp"
#include "Logger.hpp"
#include <iostream>
#include <cstring>

TaxonSet::TaxonSet(string str):
  taxa_bs(resize_clades(str))
{
  static int exists = 0;
  if (exists) {
    ERR << "Creating a second taxon set!!!!!\n\n\n";
  }
  exists = 1;
  taxa.reserve(taxa_set.size());

  for (const string& i : taxa_set) {
    add(i);
  }
  DEBUG << "Taxon Set of size " <<  size() << endl;
  for (const string& i : taxa_set) {
    DEBUG << (i) << endl;
  }  
  DEBUG << taxa_bs.str() << endl;
}


int TaxonSet::resize_clades(string str) {
  stringstream stream(str);
  string s;
  
  while(!stream.eof()) {
    getline(stream, s);
    if (s.size() == 0)
      continue;
    add_clade_taxa(s, taxa_set);
  }
  return taxa_set.size();
}

void TaxonSet::add_clade_taxa(string str, unordered_set<string>& taxa_set) {
  char* cladestr = &(str[1]);
  
  char* token;
  char* saveptr;
  
  while(token = strtok_r(cladestr, ",} ", &saveptr)) {
    cladestr = NULL;
    taxa_set.insert(string(&(token[0])));
  }
}

Taxon TaxonSet::add(const string& str) {
  if (index.count(str)) {
    return index[str];
  }
  int i = taxa.size();
  taxa.push_back(str);
  index[str] = i;
  taxa_bs.set(i);
  return i;
}  

size_t TaxonSet::size() const {
  return taxa.size();
}
