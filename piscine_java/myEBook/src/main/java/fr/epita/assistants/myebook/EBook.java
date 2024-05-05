package fr.epita.assistants.myebook;

import java.util.ArrayList;
import java.util.List;

public class EBook implements IEditable, IPaginated{
    String name;
    List<String> pages;
    int nbPages = 1;
    int current_page = 0;
    public EBook(String name)
    {
        this.name = name;
        this.pages = new ArrayList<String>();
        pages.add("");
    }
    public String getName()
    {
        return this.name;
    }
    public Book print()
    {
       Book nBook = new Book(this.name, this.pages);
       return nBook;
    }


    @Override
    public void writeCurrentPage(String pageText) {
            this.pages.remove(this.current_page);
            this.pages.add(this.current_page, pageText);
    }

    @Override
    public void addPage() {
        this.pages.add(this.current_page + 1,"");
        this.nbPages++;
    }

    @Override
    public void deletePage() {
        this.pages.remove(current_page);
        this.nbPages--;
        if (this.nbPages == 0)
        {
            this.nbPages++;
            this.pages.add("");
        }
        if (this.current_page == this.nbPages)
            this.current_page--;

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