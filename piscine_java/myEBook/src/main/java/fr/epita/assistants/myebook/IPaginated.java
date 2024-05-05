package fr.epita.assistants.myebook;

public interface IPaginated {
    void openToPage (int page);
    int getCurrentPage();
    int getPageCount();

}