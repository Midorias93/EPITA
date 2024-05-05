package fr.epita.assistants.linkedlist;

public class LinkedList<Type extends Comparable> {

    /**
     * Initializes the list
     **/
    Type elem;
    LinkedList next;

    public LinkedList() {
        elem = null;
        next = null;
    }

    /**
     * Inserts the specified element into the list.
     * The elements must be sorted in ascending order.
     * null elements should be at the end of the list.
     *
     * @param e Element to be inserted
     **/

    public Type getElem() {
        return this.elem;
    }

    public void setElem(Type e) {
        this.elem = e;
    }

    public void insert(Type e) {
        LinkedList save = this;
        LinkedList nList = new LinkedList();
        nList.setElem(e);
        if (this == null || this.getElem() == null) {
            this.setElem(e);
            return;
        }
        if (this.getElem().compareTo(e) > 0) {
            LinkedList caca = new LinkedList();
            caca.setElem(this.getElem());
            caca.next = this.next;
            this.setElem(e);
            this.next = caca;
            return;
        }
        while (save.next != null && save.getElem() != null && save.next.getElem().compareTo(e) < 0) {
            save = save.next;
        }
        if (save.next != null) {
            LinkedList save_next = save.next;
            save.next = nList;
            nList.next = save_next;
        } else
            save.next = nList;
    }

    /**
     * Returns the n-th element in the list.
     *
     * @param i Index
     * @return The element at the given index
     * @throws IndexOutOfBoundsException if there is no element at this
     *                                   index.
     **/
    public Type get(int i) {
        if (this == null || this.getElem() == null)
            throw new IndexOutOfBoundsException();
        LinkedList save = this;
        for (int j = 0; save != null && j != i; j++) {
            save = save.next;
        }
        if (save == null) {
            throw new IndexOutOfBoundsException();
        } else
            return (Type) save.getElem();
    }

    /**
     * Removes the first occurrence of the specified element in the list.
     *
     * @param e Element to remove
     * @return returns the element that has been removed or null
     **/
    public Type remove(Type e) {
        LinkedList save = this;
        if (this == null && this.getElem() == null)
            return null;
        if (this.getElem().compareTo(e) == 0) {
            if (this.next == null) {
                this.next = null;
                this.setElem(null);
                return null;
            } else {
                Type value = (Type) this.getElem();
                this.setElem((Type) this.next.getElem());
                this.next = this.next.next;
                return value;
            }
        }
        while (save.next != null && save.next.getElem() != null && save.next.getElem().compareTo(e) != 0) {
            save = save.next;
        }
        if (save.next == null)
            return null;
        else {
            Type value = (Type) save.next.getElem();
            save.next = save.next.next;
            return value;
        }
    }

    /**
     * Returns the size of the list.
     *
     * @return Number of elements in the list
     **/
    public int size() {
        int size = 0;
        if (this == null || this.getElem() == null)
            return size;
        LinkedList save = this;
        while (save != null) {
            save = save.next;
            size++;
        }
        return size;
    }

    /**
     * Removes all elements from the list.
     **/

    public void clear() {
        this.next = null;
        this.setElem(null);
    }

}
