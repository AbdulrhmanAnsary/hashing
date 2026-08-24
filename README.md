#Hashing

A C++ implementation of hash tables exploring different collision-resolution strategies and a reusable contract-based testing approach.

##Implementations

###Separate Chaining

- "BucketLinkedList"
- "BucketVector"

###Open Addressing

- Linear Probing
- Quadratic Probing
- Double Hashing

##Features

- Generic key/value types
- Configurable hash functions
- Collision handling
- Dynamic growth and shrinking
- Rehashing
- Load-factor management
- Prime-number-based capacities
- Contract tests shared across implementations
- Deterministic collision testing

##Testing

The project uses Google Test and follows a contract-testing approach.

The same behavioral contract is executed against multiple implementations using typed tests.

The tests focus on observable behavior rather than implementation details.

The test suite covers behaviors such as:

- Initial state
- Insertion
- Duplicate-key rejection
- Removal
- Missing-key handling
- Size consistency
- Growth
- Shrinking
- Grow/shrink cycles
- Large-scale insertion
- Collision behavior where applicable

Some collision scenarios are implementation-dependent. A collision test is therefore not automatically treated as a universal requirement for every hashing strategy; the algorithm's mathematical constraints must be considered when defining the appropriate contract.

##Testing Philosophy

The testing workflow used in this project is:

DEFINE
   ↓
IMAGINE USER USAGE
   ↓
IDENTIFY BEHAVIORS
   ↓
WRITE RELEVANT TESTS
   ↓
IMPLEMENT
   ↓
RUN & FIX
   ↺

The contract defines what the implementation must guarantee, while each implementation remains free to choose how that behavior is achieved.

Tests should not be weakened merely to accommodate an incorrect implementation, but neither should an artificial test condition be promoted into a universal contract when an algorithm legitimately cannot provide that behavior.

Build & Run Tests

Compile the contract tests with:

clang++ test_hashing_contract.cpp \
    -o test_hashing_contract.out \
    -lgtest \
    -lgtest_main \
    -pthread

Run:

./test_hashing_contract.out

Project Structure

The project is organized around the hashing implementations and their shared testing infrastructure.

hashing/
├── hashing_by_separate_chaining/
├── hashing_by_open_addressing/
├── math_utilities/
├── common/
└── tests/

The exact structure may evolve as the project develops.

##Design Goal

This project is primarily educational.

The goal is not simply to implement hash tables, but to explore:

- Data structure design
- Generic programming in C++
- Templates and template-template parameters
- Algorithmic trade-offs
- Contracts and behavioral specifications
- Test-driven development
- Reusable testing infrastructure
- Debugging and failure analysis
- Software engineering practices

##Status

The educational implementation is considered complete.

Further development is not required for the project's original learning objectives.

## 🤝 Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

1. Fork the Project
2. Create your Feature Branch (git checkout -b feature/AmazingFeature)
3. Commit your Changes (git commit -m 'Add some AmazingFeature')
4. Push to the Branch (git push origin feature/AmazingFeature)
5. Open a Pull Request

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.

## 📩 Contact

📧 [Email Me](abdalrhmanmohamedansarymaky@gmail.com)

🔗 Project Link: [GitHub Repository](https://github.com/AbdulrhmanAnsary/hashing.git)

Feel free to adjust any sections as needed. 🚀
