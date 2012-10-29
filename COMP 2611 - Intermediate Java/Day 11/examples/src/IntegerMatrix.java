public class IntegerMatrix extends GenericMatrix<Integer> {
  /** Implement the add method for adding two matrix elements */
  protected Integer add(Integer o1, Integer o2) {
    return new Integer(o1.intValue() + o2.intValue());
  }

  /** Implement the multiply method for multiplying two
     matrix elements */
  protected Integer multiply(Integer o1, Integer o2) {
    return new Integer(o1.intValue() * o2.intValue());
  }

  /** Implement the zero method to specify zero for Integer */
  protected Integer zero() {
    return new Integer(0);
  }
}
