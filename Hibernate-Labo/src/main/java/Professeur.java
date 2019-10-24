import javax.persistence.*;

/**
 -----------------------------------------------------------------------------------
 File        : Professeur.java
 Author(s)   : Michaël Brouchoud
 Date        : 28.12.2017

 Purpose     : Professeur represent a Professeur

 Note(s)     : -

 -----------------------------------------------------------------------------------
 */

@Entity
@Table (name="professeur")
public class Professeur implements Enseignant {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @Column
    private String prenom;

    @Column
    private String nom;

    @Column
    private String sigle;

    public  Professeur() {}

    public Professeur(String prenom, String nom) {
        this(prenom, nom, "");
    }

    public Professeur(String prenom, String nom, String sigle) {
        this.prenom = prenom;
        this.nom = nom;
        this.sigle = sigle;
    }

    public int getId() {
        return id;
    }

    private void setId(int id) {
        this.id = id;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getSigle() {
        return sigle;
    }

    public void setSigle(String sigle) {
        this.sigle = sigle;
    }

    @Override
    public String toString() {
        return prenom + " " + nom + ", " + sigle;
    }
}
