package fr.epita.assistants.myebook;

public interface IEditable {
    void writeCurrentPage(String pageText);
    void addPage();
    void deletePage();

}