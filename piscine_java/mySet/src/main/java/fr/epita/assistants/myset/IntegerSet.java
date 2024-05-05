package fr.epita.assistants.myset;

import java.util.ArrayList;

public class IntegerSet {
    public ArrayList<Integer> base_;
    public IntegerSet() {
        base_ = new ArrayList<>();
    }

    public void insert(Integer i)
    {
        if (base_.size() == 0) {
            base_.add(i);
            return;
        }
        int indice = 0;
        while (indice < base_.size() && base_.get(indice).compareTo(i) < 0) {
            indice++;
        }
        base_.add(indice, i);
    }
    public void remove(Integer i)
    {
        int indice = 0;
        while (indice != base_.size() && base_.get(indice).compareTo(i) != 0) {
            indice++;
        }
        if (indice != base_.size())
            this.base_.remove(indice);
    }
    public boolean has(Integer i)
    {
        return this.base_.contains(i);
    }
    public boolean isEmpty()
    {
        return this.base_.isEmpty();
    }
    public Integer min()
    {
        return base_.get(0);
    }
    public Integer max()
    {
        return base_.get(base_.size() - 1);
    }
    public int size()
    {
        return base_.size();
    }
    public static IntegerSet intersection(IntegerSet a, IntegerSet b)
    {
        IntegerSet nIntset = new IntegerSet();
        if (a.size() == 0 || b.size() == 0)
            return nIntset;
        for (int i = 0; i < a.size(); i++)
        {
            if (b.has(a.base_.get(i)) && !nIntset.has(a.base_.get(i)))
                nIntset.insert(a.base_.get(i));
        }
        return nIntset;
    }
    public static IntegerSet union(IntegerSet a, IntegerSet b) {
        if (a.size() == 0)
            return b;
        if (b.size() == 0)
            return a;

        IntegerSet nIntset = new IntegerSet();
        if (a.size() == 0 && b.size() == 0)
            return nIntset;

        for (int i = 0; i < a.size(); i++) {
            if (!nIntset.has(a.base_.get(i)))
                nIntset.insert(a.base_.get(i));
        }
        for (int i = 0; i < b.size(); i++) {
            if (!nIntset.has(b.base_.get(i)))
                nIntset.insert(b.base_.get(i));
        }
        return nIntset;
    }
}