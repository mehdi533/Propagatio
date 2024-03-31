# Propagatio
Propagatio Project: Course ICC (CS-199(c))
```c++11
Compile: g++ -std=c++11 -o propagatio propagatio.cc
```
```c++11
Test: ./propagatio < test_file.txt
```

The project, titled "Propagatio," focuses on understanding the propagation of information in a network. The objectives of each task are as follows:

1. **Task 1: Read input to construct an undirected graph**
   - The goal is to read an image from the standard input, verify it's square and contains only 0s and 1s, and symmetrize the image to obtain an adjacency matrix representing an undirected graph.

2. **Task 2: Verify the graph is connected**
   - The task involves checking that the graph is a single connected component, meaning there are no isolated nodes. This is done by starting from any node and recursively marking reachable nodes, ensuring the entire graph is traversable from any starting point.

3. **Task 3: Propagate information from the first node**
   - This task simulates the spread of information from the first node (node zero), displaying sorted lists of nodes that receive the information simultaneously, based on their distance from the start node.

4. **Task 4: Calculate and display the average degree of separation of the graph**
   - The final task calculates the average degree of separation across the graph, which reflects the network's cohesion and the speed at which information can be transmitted through it.
Complexity and execution time:

## The rest of this readme is part of the final report and explains <u>in French<\u> how the different tasks are implemented.

Complexity and Execution Time:

<img width="764" alt="Screenshot 2024-04-01 at 00 44 03" src="https://github.com/mehdi533/Propagatio/assets/113531778/a567c588-98a8-42d9-9bcf-7cd3bce8ae96">


* La tâche 1 est réalisée dans la fonction “initialize”, on entre les données du fichier pbm, si elles ne sont pas valides on affiche les messages d’erreurs par défaut, on a aussi entré les valeurs de la matrice d’adjacence, mis la diagonale à zéro et rendu la matrice symétrique si elle ne l’était pas. 
* Pour la tâche 2, on fait appelle à une fonction récursive "set_visited", elle note comme visités tous les noeuds qui sont connectés au noeud considéré (on commence par 0) et pour chaque noeud connectés elle se réitère et donc marque à nouveau tous les noeuds connectés à celui-ci comme visité. Cette fonction se répète jusqu’à ce que tous les nœuds aient été visités ou alors lorsqu’elle a considéré tous les noeuds reliés à zéro, dans ce cas là si il reste des noeuds non visités, le graphe n’est pas connexe (on quitte le programme et un message par défaut s’affiche). La tâche 3 et la tâche 4 sont toutes les deux effectuées dans la même fonction: count_propagation_graph. 
* La tâche 3 utilise, une fonction récursive “change_degree” répétée autant de fois que la taille de la matrice, elle fait entrer dans un tableau “degree” le nombre de nœuds rencontrés entre celui entré en paramètre et celui dont le chiffre correspond à l’emplacement dans le tableau. La première fois qu’on utilise cette fonction, on part alors du nœud 0, on obtient un tableau qui donne le nombre d’étapes pour arriver à chaque nœud, on utilise alors ce tableau pour afficher la tâche 3 en rentrant, dans l’ordre, les noeuds ayant le même degré de séparation dans un tableau de string contenant dans chaque emplacement une ligne à afficher (on utilise pour cela la fonction to_string afin de convertir les entiers en chaînes de caractères). 
* La tâche 4 est effectuée en 2 étapes: on additionne toutes les valeurs qui ont été entrées dans le vecteur “degree” et on divise cette somme par la taille de la matrice (ce qui donne la séparation moyenne des noeuds à partir de celui considéré), on additionne ensuite le résultat à une autre variable qu’on divise à nouveau par la taille de la matrice à laquelle on a soustrait 1 (puisque la fonction change_degree a été effectuée autant de fois que la taille de la matrice-1). On a alors complété toutes les tâches demandées.
