package fr.epita.assistants.maths;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

public class MatrixTests {
   @Test
   void constructeurTest1(){
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      assertEquals(m1.getMatrix(), ar);
   }

   @Test
   void consturcteurTest2() {
      Matrix m1 = new Matrix((null));
      assertNull(m1.getMatrix());
   }

   @Test
   void consturcteurTest3() {
      int[][] ar = {{1,2,3},{1,2,3,4}};
      Matrix m1 = new Matrix(ar);
      assertNull(m1);
   }

   @Test
   void consturcteurTest4() {
      int[][] ar = {};
      Matrix m1 = new Matrix(ar);
      assertEquals(m1.getMatrix(), ar);
   }

   @Test
   void equalTest1() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      assertTrue(m1.equals(m1.getMatrix()));
   }

   @Test
   void equalTest2() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      assertFalse(m1.equals(null));
   }

   @Test
   void equalTest6() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      int[][] ar2 = {{1,4,3},{2,4,5}};
      Matrix m2 = new Matrix(ar);
      assertFalse(m1.equals(m2));
   }
   @Test
   void equalTest3() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      int[][] ar2 = {{1,4,3},{2,4,5}};
      Matrix m2 = new Matrix(ar2);
      assertFalse(m1.equals(m2));
   }

   @Test
   void equalTest5() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      int[][] ar2 = {{1,4,3,5},{2,4,5}};
      Matrix m2 = new Matrix(ar);
      assertFalse(m1.equals(m2));
   }
   @Test
   void equalTest4() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      int[][] ar2 = {{1,4,3,5},{2,4,5}};
      Matrix m2 = new Matrix(ar2);
      assertFalse(m1.equals(m2));
   }

   @Test
   void multiplyTest1() {
      int[][] ar = {{1,2,3},{2,4,5}};
      Matrix m1 = new Matrix(ar);
      assertNull(m1.multiply(null));
   }

   @Test
   void multiplyTest2() {
      int[][] ar = {{1, 2, 3}, {2, 4, 5}};
      Matrix m1 = new Matrix(ar);
      int[][] ar2 = {{1, 4, 3, 5}, {2, 4, 5}};
      Matrix m2 = new Matrix(ar);
      assertNull(m1.multiply(m2));
   }


   }