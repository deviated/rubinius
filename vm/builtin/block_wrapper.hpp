#ifndef RBX_BUILTIN_BLOCK_WRAPPER_HPP
#define RBX_BUILTIN_BLOCK_WRAPPER_HPP

#include "builtin/object.hpp"
#include "type_info.hpp"

namespace rubinius {
  class BlockEnvironment;

  class BlockWrapper : public Object {
  public:
    const static object_type type = BlockWrapperType;

  private:
    BlockEnvironment* block_; // slot
    Object* lambda_; // slot

  public:
    attr_accessor(block, BlockEnvironment);
    attr_accessor(lambda, Object);

    static void init(STATE);

    // Ruby.primitive :block_wrapper_allocate
    static BlockWrapper* create(STATE, Object* self);

    Object* call(STATE, CallFrame* call_frame, size_t args);
    Object* yield(STATE, CallFrame* call_frame, size_t args);
    Object* yield(STATE, CallFrame* call_frame, Message& msg);

    // Ruby.primitive? :block_wrapper_call
    Object* call_prim(STATE, Executable* exec, CallFrame* call_frame, Message& msg);

    // Ruby.primitive? :block_wrapper_call_on_object
    Object* call_on_object(STATE, Executable* exec, CallFrame* call_frame, Message& msg);

    // Ruby.primitive :block_wrapper_from_env
    static BlockWrapper* from_env(STATE, BlockEnvironment* env);

    class Info : public TypeInfo {
    public:
      BASIC_TYPEINFO(TypeInfo)
    };
  };
}

#endif