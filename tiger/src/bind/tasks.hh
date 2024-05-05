/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

// DONE: Some code was deleted here.
#pragma once

#include <task/libtask.hh>


namespace bind::tasks
{
    TASK_GROUP("3. Bind");


    TASK_DECLARE("b|bindings-compute", "compute bindings", bindings_compute, "parse");

    TASK_DECLARE("B|bindings-display", "fait bindings display", bindings_display, "parse");

    TASK_DECLARE("rename", "rename je sais pas quoi encore", renamer_compute, "bound");

    DISJUNCTIVE_TASK_DECLARE("bound", "bound", "bindings_compute");

//DONE a faire si on veut faire l'OOB TASK_DECLARE("object-bindings-compute", "fait object bindings",object_bindings_compute, "")

}
