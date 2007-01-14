class MRITargetError < RuntimeError; end

class RubiniusSpecExample; end

module MRITarget
  def example(src='', &block)
    raise ArgumentError, "you must pass a block" unless block_given?
    Object.class_eval(src)
    yield
  end
end
