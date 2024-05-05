package fr.epita.assistants.myebook;

import java.util.ArrayList;
import java.util.List;

public class EBookReader implements IUpdatable, IReadable, IPaginated {
    double firmware;
    Book book;
    public EBookReader()
    {
        this.firmware = 1.0;
    }

    public void openEbook(EBook ebook)
    {
        this.book = ebook.print();
    }

    @Override
    public String readCurrentPage() {
        if (this.book != null)
            return this.book.pages.get(book.current_page);
        return null;
    }

    @Override
    public void openToPage(int page) {
        if(page >= 0 && page < this.book.nbPages)
            this.book.current_page = page;
    }

    @Override
    public int getCurrentPage() {
       if (book != null)
            return this.book.current_page;
       return -1;
    }

    @Override
    public int getPageCount() {
        if (book != null)
            return this.book.nbPages;
        return -1;
    }

    @Override
    public double getVersion() {
        return this.firmware;
    }

    @Override
    public void update(double version) {
        if (version > this.firmware)
            this.firmware = version;
    }
}