import javax.persistence.*;

/**
 -----------------------------------------------------------------------------------
 File        : ChargeDeCours.java
 Author(s)   : Michaël Brouchoud
 Date        : 28.12.2017

 Purpose     : ChargeDeCours represent a ChargeDeCours

 Note(s)     : -

 -----------------------------------------------------------------------------------
 */

@Entity
@Table(name="charge_de_cours")
public class ChargeDeCours implements Enseignant {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @Column
    private String nomComplet;

    public ChargeDeCours() {}

    public ChargeDeCours(String nomComplet) {
        this.nomComplet = nomComplet;
    }

    public int getId() {
        return id;
    }

    private void setId(int id) {
        this.id = id;
    }

    public String getNomComplet() {
        return nomComplet;
    }

    public void setNomComplet(String nomComplet) {
        this.nomComplet = nomComplet;
    }

    @Override
    public String toString() {
        return nomComplet;
    }
}
