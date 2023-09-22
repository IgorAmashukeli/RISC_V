#include <assert.h>
#include <bits/stdc++.h>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
Assembler for RISC V ISA


**/

/**remove commas from instruction**/
void decommer(string &instruction) {
  // erase + remove idiom
  instruction.erase(remove(instruction.begin(), instruction.end(), ','),
                    instruction.end());
}

/**split instruction into tokens**/
vector<string> split(const string &instruction) {
  // vector of tokens
  vector<string> tokens;

  // get stringstream
  stringstream ss(instruction);

  // get tokens
  string token;
  while (ss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

/**RV32I encoder**/
class RV32I_Encoder {
public:
  /**encoder init**/
  RV32I_Encoder(std::string &instruction) {
    // delete commas in instruction
    decommer(instruction);

    // split instruction into tokens
    instruction_elements_ = split(instruction);

    // assert the instruction has at least one token
    assert(instruction_elements_.size() >= 1);
  }

  /**opcode

  RV32I opcode table:

  B type:      1100011
  some I type: 0000011
  S type:      0100011
  some I type: 0010011
  R type:      0110011
  some I type: 1110011
  lui:         0110111
  auipc:       0010111
  jal:         1101111
  jalr:        1100111
  ecall:       1110011
  ebreak:      1110011

  **/
  void create_opcode() {
    // get instruction name
    string instruction_name = instruction_elements_[0];

    // B type instruction names
    unordered_set<string> B_TYPE = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};

    // some I type instruction names
    unordered_set<string> I_TYPE1 = {"lb", "lh", "lw", "lbu", "lhu"};

    // S type instruction names
    unordered_set<string> S_TYPE = {"sb", "sh", "sw"};

    // some other I type instruction names
    unordered_set<string> I_TYPE2 = {"addi", "slti", "sltiu", "xori", "ori",
                                     "andi", "slli", "srli",  "srai"};

    // R type instruction names
    unordered_set<string> R_TYPE = {"add", "sub", "sll", "slt", "sltu",
                                    "xor", "srl", "sra", "or",  "and"};

    // some other I type instruction names
    unordered_set<string> I_TYPE3 = {"csrrw",  "csrrs",  "csrrc",
                                     "csrrwi", "csrrsi", "csrrci"};

    // B type opcode
    if (B_TYPE.find(instruction_name) != B_TYPE.end()) {
      opcode_ = "1100011";
    }
    // some of I type instructions opcode
    else if (I_TYPE1.find(instruction_name) != I_TYPE1.end()) {
      opcode_ = "0000011";
    }
    // S type opcode
    else if (S_TYPE.find(instruction_name) != S_TYPE.end()) {
      opcode_ = "0100011";
    }
    // some of other I type instructions opcode
    else if (I_TYPE2.find(instruction_name) != I_TYPE2.end()) {
      opcode_ = "0010011";
    }
    // R type opcode
    else if (R_TYPE.find(instruction_name) != R_TYPE.end()) {
      opcode_ = "0110011";
    }
    // some of other I type instructios opcode
    else if (I_TYPE3.find(instruction_name) != I_TYPE3.end()) {
      opcode_ = "1110011";
    }

    // other instructions

    else if (instruction_name == "lui") {
      opcode_ = "0110111";
    } else if (instruction_name == "auipc") {
      opcode_ = "0010111";
    } else if (instruction_name == "jal") {
      opcode_ = "1101111";
    } else if (instruction_name == "jalr") {
      opcode_ = "1100111";
    } else if (instruction_name == "fence") {
      opcode_ = "0001111";
    } else if (instruction_name == "ecall") {
      opcode_ = "1110011";
    } else if (instruction_name == "ebreak") {
      opcode_ = "1110011";
    } else {
      // other instructions doesn't exist
      assert(false);
    }

    return;
  }

private:
  // instruction
  vector<string> instruction_elements_;

  // opcode
  string opcode_;

  // binary code
  string binary_code_;
};
