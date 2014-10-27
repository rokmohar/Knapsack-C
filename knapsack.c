#include <stdio.h>
#include <stdlib.h>
 
typedef struct node node;
 
struct node {
    // Weight
    long int weight;
    
    // Profit
    long int profit;
    
    // Next node
    node *next;
};
 
/**
 * @param node* dst
 * @param node* ele
 * 
 * @return int
 */
int validateNode(node *dst, node *ele)
{
    // Temporary pointer
    node *temp = dst;
    
    // Iteration through nodes
    while (temp != NULL) {
        // Check if node size is invalid
        if (temp->weight <= ele->weight && ele->profit <= temp->profit) {
            // Node is invalid
            return 0;
        }
        
        // Set next node
        temp = temp->next;
    }
    
    // Nove is valid
    return 1;
}
 
/**
 * @param node* dst
 * @param node* src
 * 
 * @return node*
 */
node *mergeTree(node *dst, node *src)
{
    // Temporary pointer
    node *temp = src;
    
    // Iteration through nodes
    while (temp != NULL) {
        // Set next node
        node *next = temp->next;
        
        // Check if node is valid
        if (validateNode(dst, temp) == 1) {
            // Add node to next tree level
            temp->next = dst;
            
            // Set first node
            dst = temp;
        }
        else {
            // Free memory
            free(temp);
        }
        
        // Set next node
        temp = next;
    }
    
    return dst;
}
 
/**
 * @param long int maxWeight
 * @param node*    tree1
 * @param long int weight
 * @param long int profit
 * 
 * @return node*
 */
node *addNode(long int maxWeight, node *tree1, long int weight, long int profit)
{
    // Check if node size is valid
    if (weight <= maxWeight) {
        // Temporary pointer
        node *temp = tree1;
        
        node *tree2 = NULL;
        
        // Iteration through nodes
        while (temp != NULL) {
            // Check if new size is valid
            if (temp->weight + weight <= maxWeight) {
                // Create new node
                node *insert = (node *) malloc(sizeof(node));
                
                // Check if node is invalid
                if (insert == NULL) {
                    // Terminate program
                    exit(1);
                }
                
                // Set node data
                insert->weight = (temp->weight + weight);
                insert->profit = (temp->profit + profit);
                insert->next   = tree2;
                
                // Set first node
                tree2 = insert;
            }
            
            // Set next node
            temp = temp->next;
        }
        
        // Merge tree levels and return merged tree
        return mergeTree(tree2, tree1);
    }
    
    // Return original tree
    return tree1;
}
 
/**
 * @param int   argc
 * @param char* argv[]
 * 
 * @return int
 */
int main(int argc, char *argv[])
{
    long int maxWeight = 0;
    long int itemsNo   = 0;
    
    // Max weight
    scanf("%ld", &maxWeight);
    
    // First node
    node *tree = (node *) malloc(sizeof(node));
    
    // Check if node is invalid
    if (tree == NULL) {
        // Terminate program
        exit(1);
    }
    
    // Set node data
    tree->weight = 0;
    tree->profit = 0;
    tree->next   = NULL;
    
    // Read and add nodes from file
    for (long int weight, profit; scanf("%ld %ld", &weight, &profit) != EOF; itemsNo++) {
        // Add node to tree
        tree = addNode(maxWeight, tree, weight, profit);
    }
    
    // Maximum profit value
    long int maxProfit = 0;
    
    // Iteration through last tree level
    while (tree != NULL) {
        // Next node
        node *next = tree->next;
        
        // Check if profit is greater than current maximum
        if (maxProfit < tree->profit) {
            // Set new maximum profit
            maxProfit = tree->profit;
        }
        
        // Free memory
        free(tree);
        
        // Set next node
        tree = next;
    }
    
    // Print maximum profit value
    printf("%ld\n", maxProfit);
    
    return 0;
}
