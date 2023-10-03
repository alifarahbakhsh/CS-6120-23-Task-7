#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <string.h>

using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
        errs() << "Before swapping:\n";
        for (auto &F : M) {
            for (auto &B : F) {
                for (auto &I : B) {
                    errs() << I << "!\n";
                }
            }
        }
        for (auto &F : M) {
            for (auto &B : F) {
                for (auto &I : B) {
                    if (I.getOpcode() == Instruction::Add) {
                        auto* op = dyn_cast<BinaryOperator>(&I);
                        op->swapOperands();
                    }
                    if (I.getOpcode() == Instruction::Mul) {
                        auto* op = dyn_cast<BinaryOperator>(&I);
                        op->swapOperands();
                    }
                }
            }
        }
        errs() << "After swapping:\n";
        for (auto &F : M) {
            for (auto &B : F) {
                for (auto &I : B) {
                    errs() << I << "!\n";
                }
            }
        }
        return PreservedAnalyses::all();
    };
};

}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "Skeleton pass",
        .PluginVersion = "v0.1",
        .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                    MPM.addPass(SkeletonPass());
                });
        }
    };
}
