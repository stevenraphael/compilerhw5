module attributes {dlti.dl_spec = #dlti.dl_spec<!llvm.ptr<270> = dense<32> : vector<4xi64>, !llvm.ptr<271> = dense<32> : vector<4xi64>, !llvm.ptr<272> = dense<64> : vector<4xi64>, i64 = dense<64> : vector<2xi64>, i128 = dense<128> : vector<2xi64>, f80 = dense<128> : vector<2xi64>, !llvm.ptr = dense<64> : vector<4xi64>, i1 = dense<8> : vector<2xi64>, i8 = dense<8> : vector<2xi64>, i16 = dense<16> : vector<2xi64>, i32 = dense<32> : vector<2xi64>, f16 = dense<16> : vector<2xi64>, f64 = dense<64> : vector<2xi64>, f128 = dense<128> : vector<2xi64>, "dlti.endianness" = "little", "dlti.mangling_mode" = "e", "dlti.legal_int_widths" = array<i32: 8, 16, 32, 64>, "dlti.stack_alignment" = 128 : i64>, llvm.ident = "Ubuntu clang version 21.1.8 (6ubuntu1)", llvm.module_asm = [], llvm.target_triple = "x86_64-pc-linux-gnu"} {
  llvm.mlir.global private unnamed_addr constant @".str"("%d\00") {addr_space = 0 : i32, alignment = 1 : i64, dso_local}
  llvm.mlir.global private unnamed_addr constant @".str.1"("Hello, %s!\0A\00") {addr_space = 0 : i32, alignment = 1 : i64, dso_local}
  llvm.module_flags [#llvm.mlir.module_flag<error, "wchar_size", 4 : i32>, #llvm.mlir.module_flag<min, "PIC Level", 2 : i32>, #llvm.mlir.module_flag<max, "PIE Level", 2 : i32>, #llvm.mlir.module_flag<max, "uwtable", 2 : i32>, #llvm.mlir.module_flag<max, "frame-pointer", 2 : i32>]
  llvm.func @main(%arg0: i32 {llvm.noundef}, %arg1: !llvm.ptr {llvm.noundef}) -> i32 attributes {dso_local, frame_pointer = #llvm.framePointerKind<all>, no_inline, no_unwind, optimize_none, passthrough = [["min-legal-vector-width", "0"], ["no-trapping-math", "true"], ["stack-protector-buffer-size", "8"], ["target-cpu", "x86-64"]], target_cpu = "x86-64", target_features = #llvm.target_features<["+cmov", "+cx8", "+fxsr", "+mmx", "+sse", "+sse2", "+x87"]>, tune_cpu = "generic", uwtable_kind = #llvm.uwtableKind<async>} {
    %0 = llvm.mlir.constant(1 : i32) : i32
    %1 = llvm.mlir.constant(0 : i32) : i32
    %2 = llvm.mlir.constant(61440 : i32) : i32
    %3 = llvm.mlir.constant(12 : i32) : i32
    %4 = llvm.mlir.constant(15 : i32) : i32
    %5 = llvm.mlir.constant(3 : i32) : i32
    %6 = llvm.mlir.addressof @".str" : !llvm.ptr
    %7 = llvm.mlir.addressof @".str.1" : !llvm.ptr
    %8 = llvm.alloca %0 x i32 {alignment = 4 : i64} : (i32) -> !llvm.ptr
    %9 = llvm.alloca %0 x i32 {alignment = 4 : i64} : (i32) -> !llvm.ptr
    %10 = llvm.alloca %0 x !llvm.ptr {alignment = 8 : i64} : (i32) -> !llvm.ptr
    %11 = llvm.alloca %0 x i32 {alignment = 4 : i64} : (i32) -> !llvm.ptr
    %12 = llvm.alloca %0 x i32 {alignment = 4 : i64} : (i32) -> !llvm.ptr
    %13 = llvm.alloca %0 x !llvm.array<12 x i8> {alignment = 1 : i64} : (i32) -> !llvm.ptr
    llvm.store %1, %8 <alignment = 4> : i32, !llvm.ptr
    llvm.store %arg0, %9 <alignment = 4> : i32, !llvm.ptr
    llvm.store %arg1, %10 <alignment = 8> : !llvm.ptr, !llvm.ptr
    %14 = llvm.load %10 <alignment = 8> : !llvm.ptr -> !llvm.ptr
    %15 = llvm.getelementptr inbounds %14[1] : (!llvm.ptr) -> !llvm.ptr, !llvm.ptr
    %16 = llvm.load %15 <alignment = 8> : !llvm.ptr -> !llvm.ptr
    %17 = llvm.call @atoi(%16) {memory_effects = #llvm.memory_effects<other = read, argMem = read, inaccessibleMem = read, errnoMem = read, targetMem0 = read, targetMem1 = read>, no_unwind, will_return} : (!llvm.ptr {llvm.noundef}) -> i32
    llvm.store %17, %11 <alignment = 4> : i32, !llvm.ptr
    %18 = llvm.load %11 <alignment = 4> : !llvm.ptr -> i32
    %19 = llvm.and %18, %2 : i32
    %20 = llvm.lshr %19, %3 : i32
    %21 = llvm.and %18, %4 : i32
    %22 = llvm.add %20, %21 : i32
    %23 = llvm.and %22, %5 : i32
    llvm.store %23, %12 <alignment = 4> : i32, !llvm.ptr
    %24 = llvm.getelementptr inbounds %13[0, 0] : (!llvm.ptr) -> !llvm.ptr, !llvm.array<12 x i8>
    %25 = llvm.load %12 <alignment = 4> : !llvm.ptr -> i32
    %26 = llvm.call @sprintf(%24, %6, %25) vararg(!llvm.func<i32 (ptr, ptr, ...)>) {no_unwind} : (!llvm.ptr {llvm.noundef}, !llvm.ptr {llvm.noundef}, i32 {llvm.noundef}) -> i32
    %27 = llvm.call @printf(%7, %24) vararg(!llvm.func<i32 (ptr, ...)>) : (!llvm.ptr {llvm.noundef}, !llvm.ptr {llvm.noundef}) -> i32
    llvm.return %1 : i32
  }
  llvm.func @atoi(!llvm.ptr {llvm.noundef}) -> i32 attributes {frame_pointer = #llvm.framePointerKind<all>, memory_effects = #llvm.memory_effects<other = read, argMem = read, inaccessibleMem = read, errnoMem = read, targetMem0 = read, targetMem1 = read>, no_unwind, passthrough = [["no-trapping-math", "true"], ["stack-protector-buffer-size", "8"], ["target-cpu", "x86-64"]], target_cpu = "x86-64", target_features = #llvm.target_features<["+cmov", "+cx8", "+fxsr", "+mmx", "+sse", "+sse2", "+x87"]>, tune_cpu = "generic", will_return}
  llvm.func @sprintf(!llvm.ptr {llvm.noundef}, !llvm.ptr {llvm.noundef}, ...) -> i32 attributes {frame_pointer = #llvm.framePointerKind<all>, no_unwind, passthrough = [["no-trapping-math", "true"], ["stack-protector-buffer-size", "8"], ["target-cpu", "x86-64"]], target_cpu = "x86-64", target_features = #llvm.target_features<["+cmov", "+cx8", "+fxsr", "+mmx", "+sse", "+sse2", "+x87"]>, tune_cpu = "generic"}
  llvm.func @printf(!llvm.ptr {llvm.noundef}, ...) -> i32 attributes {frame_pointer = #llvm.framePointerKind<all>, passthrough = [["no-trapping-math", "true"], ["stack-protector-buffer-size", "8"], ["target-cpu", "x86-64"]], target_cpu = "x86-64", target_features = #llvm.target_features<["+cmov", "+cx8", "+fxsr", "+mmx", "+sse", "+sse2", "+x87"]>, tune_cpu = "generic"}
}

