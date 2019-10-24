/**
 -----------------------------------------------------------------------------------
 File        : Inscription.java
 Author(s)   : Michaël Brouchoud
 Date        : 11.12.2017

 Purpose     : Inscription represent a Inscription From a Student to a Cours

 Note(s)     : -

 -----------------------------------------------------------------------------------
 */

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "inscriptions")
public class Inscription {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @Column
    private char grade;

    @ManyToOne
    @JoinColumn(name = "cours_id", nullable = false)
    private Cours cours;

    @ManyToOne
    @JoinColumn(name = "etudiant_id", nullable = false)
    private Etudiant etudiant;

    public Inscription() {}

    public Inscription(Cours cours, Etudiant etudiant) {
        this.etudiant = etudiant;
        this.cours = cours;
    }

    public Inscription(Cours cours, Etudiant etudiant, char grade) {
        this.etudiant = etudiant;
        this.cours = cours;
        this.grade = grade;
    }

    public int getId() {
        return id;
    }

    private void setId(int id) {
        this.id = id;
    }

    public char getGrade() {
        return grade;
    }

    public void setGrade(char grade) {
        this.grade = grade;
    }

    public Cours getCours() {
        return cours;
    }

    public void setCours(Cours cours) {
        this.cours = cours;
    }

    public Etudiant getEtudiant() {
        return etudiant;
    }

    public void setEtudiant(Etudiant etudiant) {
        this.etudiant = etudiant;
    }

    public boolean equals(Inscription inscription) {
        return this.id == inscription.id;
    }
}
