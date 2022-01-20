// The Map class is implemented as a connected graph. The graph’s nodes represents a
// territory (implemented as a Territory class). Edges between nodes represent adjacency
// between territories
// Continents are connected subgraphs. Each territory belongs to one and only one continent.
// A territory is owned by a player and contain a number of armies.
// The Map class can be used to represent any map graph configuration.
// The Map class includes a validate() method that makes the following checks: 1) the map is
// a connected graph, 2) continents are connected subgraphs and 3) each country belongs to
// one and only one continent. 