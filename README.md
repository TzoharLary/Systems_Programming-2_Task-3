## Catan Game

### Overview

This project implements a simplified version of the Catan board game in C++. The implementation includes classes for the board, players, tiles, roads, vertices, development cards, and game logic, adhering to the provided rules.

### Files

- **src/board.hpp** and **src/board.cpp**: Defines and implements the Board class, which handles the setup and management of the game board.
- **src/player.hpp** and **src/player.cpp**: Defines and implements the Player class, which represents players and their actions.
- **src/tile.hpp** and **src/tile.cpp**: Defines and implements the Tile class, representing the resources and vertices of a board tile.
- **src/road.hpp** and **src/road.cpp**: Defines and implements the Road class, representing the roads between vertices.
- **src/vertex.hpp** and **src/vertex.cpp**: Defines and implements the Vertex class, representing points where players can build settlements or cities.
- **src/developmentCard.hpp** and **src/developmentCard.cpp**: Defines and implements various development cards such as Monopoly, Road Building, Knight, and Victory Point cards.
- **src/validator.hpp** and **src/validator.cpp**: Defines and implements the Validator class, which ensures player actions and board states are valid.
- **src/catan.hpp** and **src/catan.cpp**: Defines and implements the Catan class, which manages the overall game flow and rules.
- **src/main.cpp**: The main entry point of the application demonstrating one round of the game.
- **tests/tests.cpp**: Unit tests for the classes.
- **Makefile**: Build configuration.
- **README.md**: This file.

### Building and Running

#### Build the Project

```bash
make
```

#### Run the Tests

```bash
make test

```

#### Run the Application

```bash
./catan 
```

#### Combined Build and Run

To both build and run the application in one step, use:

```bash
make catan
```



### Design Considerations

The project implements key object-oriented programming (OOP) principles:

1. **Encapsulation**:
   - Each class has private fields managed by public methods.
   - Headers (`.hpp`) define interfaces, while source files (`.cpp`) hide implementation details.

2. **Single Responsibility Principle (SRP)**:
   - Each class focuses on a specific role (e.g., `Player` manages player actions, `Board` manages game state).

3. **Polymorphism**:
   - Enables using a single interface (`DevelopmentCard`) to handle various card types with unique behavior.

### Class Details and Relationships

#### Board

- **Purpose**: Manages the overall game board, including tiles, vertices, roads, and resource distribution.
- **Key Methods**:
  - `setup()`: Initializes the board components.
  - `getTilesForVertex(int vertexIndex)`: Returns tiles associated with a given vertex.
  - `createRoads()` / `createVertices()`: Builds roads and vertices for the board.
- **Relationships**:
  - Contains and manages `Tile`, `Vertex`, and `Road` objects.
  - `friend` of `Player`, `Validator`, and `Catan` for access to internal logic.

#### Player

- **Purpose**: Represents a player in the game, managing resources, settlements, and development cards 
- **Key Fields**:
  - `resources`: Tracks the player's resources.
  - `settlements`: Indexes of settlements built by the player.
  - `developmentCards`: Stores the player's development cards.
- **Key Methods**:
  - `placeSettlement(int vertexIndex)`: Places a settlement on the board.
  - `upgradeSettlementToCity(int vertexIndex)`: Upgrades a settlement to a city.
  - `buyDevelopmentCard()`: Purchases a development card.
- **Relationships**:
  - Interacts with `Board` for actions like building settlements and roads.
  - `friend` of `KnightCard`, `VictoryPointCard`, and `Validator` for card logic.

#### Tile

- **Purpose**: Represents individual tiles on the board, each with a resource type and associated vertices.
- **Key Fields**:
  - `TileId`: Unique identifier for the tile.
  - `TileResource`: Resource type produced by the tile.
  - `TileVertices`: Vertices associated with the tile.
- **Key Methods**:
  - `getVertex(int id)`: Retrieves a vertex by index.
  - `getAdjacentTiles()`: Lists neighboring tiles.
- **Relationships**:
  - Connected to `Vertex` objects for resource distribution.

#### Road

- **Purpose**: Represents roads connecting vertices on the board.
- **Key Fields**:
  - `betweenVertices`: The vertices connected by the road.
  - `OwnerPlayer`: The player who owns the road.
- **Key Methods**:
  - `isOccupied()`: Checks if the road is occupied.
- **Relationships**:
  - Interacts with `Player` for ownership.
  - `friend` of `Board` for board setup.

#### Vertex

- **Purpose**: Represents points on the board where players can build settlements or cities.
- **Key Fields**:
  - `type`: Indicates if the vertex is a settlement, city, or empty.
  - `player`: Tracks the player occupying the vertex.
- **Key Methods**:
  - `setVertexProperties(VertexType newType, Player* p)`: Sets vertex type and ownership.
  - `getAdjacentVertices()`: Lists neighboring vertices.
- **Relationships**:
  - Connected to `Tile` for resource distribution.
  - `friend` of `Player` and `Board` for construction logic.

#### DevelopmentCard

- **Purpose**: Represents development cards with unique benefits.
- **Key Derived Classes**:
  - `MonopolyCard`: Grants all resources of a specific type.
  - `RoadBuildingCard`: Allows building additional roads.
  - `KnightCard`: Provides knight-related benefits.
  - `VictoryPointCard`: Grants victory points.
- **Key Methods**:
  - `applyBenefit(Player* player, variant<vector<ResourceType>, pair<int, int>> benefit)`: Applies the card's effect.

#### Validator

- **Purpose**: Validates player actions such as trading and building.
- **Key Methods**:
  - `validatePlayer()`: Checks if player actions are valid.
- **Relationships**:
  - Interacts with `Board` and `Player` for validation logic.

#### Catan

- **Purpose**: Manages the overall game flow, including turns and resource distribution.
- **Key Methods**:
  - `advanceTurn()`: Moves the game to the next player's turn.
  - `distributeResources(int rolledNumber)`: Allocates resources based on dice roll.
- **Relationships**:
  - Controls the interactions between `Player` and `Board`.

### Dependencies

- **g++**: GNU Compiler Collection for building the project.
- **Google Test**: Framework used for unit tests.

### Contact

For any questions, please contact: **[tzohary1234@gmail.com](mailto\:tzohary1234@gmail.com)**.

