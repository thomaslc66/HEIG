/**
 -----------------------------------------------------------------------------------
 File        : CoursExterieur.java
 Author(s)   : Michaël Brouchoud
 Date        : 28.12.2017

 Purpose     : CoursExterieur represent a CoursExterieur

 Note(s)     : -

 -----------------------------------------------------------------------------------
 */

import javax.persistence.*;

@Entity
@Table(name="cours_exterieur")
@PrimaryKeyJoinColumn(name = "id")
public class CoursExterieur extends Cours {
    @Column
    private String ecole;

    public CoursExterieur() {}

    public CoursExterieur(String titre, int credits, String ecole) {
        super(titre, credits);
        this.ecole = ecole;
    }

    public String getEcole() {
        return ecole;
    }

    public void setEcole(String ecole) {
        this.ecole = ecole;
    }

    @Override
    public String toString() {
        return "Caractéristiques : Cours Exterieur, " + this.getEnseignant();
    }
}
