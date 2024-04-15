# GASATHON

Binging this [course](https://www.udemy.com/course/unreal-engine-5-gas-top-down-rpg/)

The project is organized as a monolothic module with an auxillary editor module.

Implementation design perfs:

* Keep data structures and codepaths flat with minimal abstraction patterns
  * Lift to more specific or generalized code-pathsonly when necessary
  * Minimize distinct code-paths
  * Use classes as "filters", keep things "mega-structed"
    * Use composition for large sets of entiites (when possible).
  * Never pre-emtively make interfaces or interface-like patterns
* Keep everything data-wise in the runtime unless there is a measurable performance cost.
* Some exploratory optimizations for educational purposes.
* Plugins are installed in the engine repo unless not possible.
* Code almost exclusively in C++ for everything but cosmetics (this is an engineering portfolio piece).
* Keep static module functions within C++ namesapces and have the in BP function libraries to expose to BPs.
* Perfer stage-metaprogramming to C++ compiler provided templating (when possible).
