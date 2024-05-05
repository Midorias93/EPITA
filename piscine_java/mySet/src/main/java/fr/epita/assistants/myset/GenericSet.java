package fr.epita.assistants.myset;

import java.util.ArrayList;

public class GenericSet<Type extends Comparable> {
    public ArrayList<Type> base_;
    public GenericSet() {
        base_ = new ArrayList<>();
    }

    public void insert(Type i)
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
    public void remove(Type i)
    {
        int indice = 0;
        while (indice != base_.size() && base_.get(indice).compareTo(i) != 0) {
            indice++;
        }
        if (indice != base_.size())
            this.base_.remove(indice);
    }
    public boolean has(Type i)
    {
        return this.base_.contains(i);
    }
    public boolean isEmpty()
    {
        return this.base_.isEmpty();
    }
    public Type min()
    {
        return base_.get(0);
    }
    public Type max()
    {
        return base_.get(base_.size() - 1);
    }
    public int size()
    {
        return base_.size();
    }
    public static GenericSet intersection(GenericSet a, GenericSet b)
    {
        GenericSet nIntset = new GenericSet();
        if (a.size() == 0 || b.size() == 0)
            return nIntset;
        for (int i = 0; i < a.size(); i++)
        {
            if (b.has((Comparable) a.base_.get(i)) && !nIntset.has((Comparable) a.base_.get(i)))
                nIntset.insert((Comparable) a.base_.get(i));
        }
        return nIntset;
    }
    public static GenericSet union(GenericSet a, GenericSet b) {
        if (a.size() == 0)
            return b;
        if (b.size() == 0)
            return a;

        GenericSet nIntset = new GenericSet();
        if (a.size() == 0 && b.size() == 0)
            return nIntset;

        for (int i = 0; i < a.size(); i++) {
            if (!nIntset.has((Comparable) a.base_.get(i)))
                nIntset.insert((Comparable) a.base_.get(i));
        }
        for (int i = 0; i < b.size(); i++) {
            if (!nIntset.has((Comparable) b.base_.get(i)))
                nIntset.insert((Comparable) b.base_.get(i));
        }
        return nIntset;
    }
}
