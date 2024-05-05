package com.epita.creeps.build;

import com.epita.creeps.given.vo.Resources;
import com.epita.creeps.given.vo.geometry.Point;

public class Townhall extends Build {
    public Resources inventaire;
    public Townhall(boolean isSafePlace, Point co, Resources inventaire) {
        super(isSafePlace, co);
        this.inventaire = inventaire;
    }
}
