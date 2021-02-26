import java.util.Stack;
import java.util.Scanner; 

class Main {
    public static boolean validateStackSequences(int[] pushed, int[] popped) {
        int N = pushed.length;
        Stack<Integer> stack = new Stack();

        int j = 0;
        for (int x : pushed) {
            stack.push(x);
            while (!stack.isEmpty() && j < N && stack.peek() == popped[j]) {
                stack.pop();
                j++;
            }
        }

        return j == N;
    }

    public static void main(String[] args) {
        Scanner myObj = new Scanner(System.in);

        int[] pushed = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int[] poped;
        
        

        if (validateStackSequences(pushed, poped)) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }
}