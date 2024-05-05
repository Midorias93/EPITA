package fr.epita.assistants.myebook;

import java.util.ArrayList;
import java.util.List;

public class Book implements IReadable ,IPaginated{
    String name;
    List<String> pages;
    final int nbPages;
    int current_page = 0;

     Book(String name, List<String> pages) {
         this.name = name;
        if (pages != null && pages.size() == 0) {
            nbPages = 1;

            this.pages = new ArrayList<String>();
            this.pages.add("");
        }
        else {
            nbPages = pages.size();
            this.pages = new ArrayList<>(pages);
        }
    }
    public String getName() {
        return this.name;
    }
    public EBook scan() {
        EBook nEbook = new EBook(this.name);
        nEbook.nbPages = this.nbPages;
        nEbook.pages = new ArrayList<>(pages);
        return nEbook;
    }
    @Override
    public String readCurrentPage() {
        return this.pages.get(current_page);
    }

    @Override
    public void openToPage(int page) {
         if(page >= 0 && page < this.nbPages)
             this.current_page = page;
    }

    @Override
    public int getCurrentPage() {
         return this.current_page;
    }

    @Override
    public int getPageCount() {
         return this.nbPages;
    }
}