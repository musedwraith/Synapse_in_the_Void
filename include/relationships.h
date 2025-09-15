#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H

// defines the maximum length for the string for Relationship
// this is the TYPE of relationship
#define MAX_REL_TYPE_LENGTH 100

// defines the maximum length for the string for details regarding the relationship
// information about the relationship
#define MAX_DETAIL_LENGTH 200

// holds information about two characters - the direct edge between 2 nodes
// for the data type Relationship, each Relationship variable will store
// a source character: "from"
// a target character: "to"
// a description of the relationship type: "label"
typedef struct {
    char from[MAX_DETAIL_LENGTH];
    char to[MAX_DETAIL_LENGTH];
    char label[MAX_DETAIL_LENGTH];
} Relationship;

void add_relationship(Relationship** relationships, int* rel_count, int* rel_capacity);
void list_relationships(Relationship* relationships, int rel_count);

#endif
