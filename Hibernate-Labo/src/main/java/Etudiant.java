/**
 -----------------------------------------------------------------------------------
 File        : Etudiant.java
 Author(s)   : Thomas Lechaire
 Date        : 04.12.2017

 Purpose     : Etudiant represent a Etudiant

 Note(s)     : -

 -----------------------------------------------------------------------------------
 */

import com.sun.javafx.runtime.eula.Eula;
import com.sun.org.apache.xpath.internal.operations.Equals;
import org.hibernate.Session;
import org.hibernate.Transaction;

import javax.persistence.*;
import java.io.Serializable;
import java.time.*;
import java.util.*;

@Entity
@Table(name = "etudiants")
public class Etudiant {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @Column
    private String prenom;

    @Column
    private String nom;

    @Column
    private LocalDate date;

    @OneToMany(targetEntity = Inscription.class, fetch = FetchType.LAZY,
            cascade=CascadeType.ALL, mappedBy = "etudiant", orphanRemoval = true)
    private Set<Inscription> inscriptions = new HashSet<Inscription>();

    @Transient
    private Set<Cours> listeDeCours = new HashSet<Cours>();

    @Transient
    private Set<Enseignant> listeEnseignants = new HashSet<Enseignant>();


    public Etudiant(){}

    public Etudiant(String nom){
        this.nom = nom;
    }

    public Etudiant(String nom, String prenom){
        this.prenom = prenom;
        this.nom = nom;
    }

    public Etudiant(String prenom, String nom, LocalDate date){
        this.prenom = prenom;
        this.nom = nom;
        this.date = date;
    }

    public void ajouterCours(Cours cours) {
        inscriptions.add(new Inscription(cours, this));
    }

    public Set<Cours> getCours(){
        listeDeCours.clear();
        for (Inscription inscr : inscriptions){
            listeDeCours.add(inscr.getCours());
        }
        return listeDeCours;
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

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public Set<Inscription> getInscriptions() {
        return inscriptions;
    }

    public void setInscriptions(Set<Inscription> inscriptions) {
        this.inscriptions = inscriptions;
    }

    public void attribuerGrade(Cours cours, char grade, Session session) {
        boolean coursTrouve = false;
        for(Inscription inscr : inscriptions) {
            if(inscr.getCours() == cours) {
                coursTrouve = true;
                Transaction transaction = session.beginTransaction();
                inscr.setGrade(grade);
                session.saveOrUpdate(inscr);
                transaction.commit();
            }
        }

        if(!coursTrouve) {
            throw new IndexOutOfBoundsException("L'etudiant : " + this.prenom + " " + this.nom + " n'est pas encore inscrit au cours : " + cours.getTitre());
        }
    }

    public boolean equals(Etudiant etudiant) {
        return  this.id == etudiant.id;
    }

    public List<Cours> coursNonCredites(Session session) {
        List<Object[]> querry = session.createQuery("from Etudiant as e join e.inscriptions as i join i.cours as c where i.grade = '\u0000' and e.id = " + this.id).list();

        ArrayList<Cours> coursNonCredit = new ArrayList<Cours>();

        for (Object[] o : querry) {
            coursNonCredit.add((Cours)o[2]);
        }

        return coursNonCredit;
    }

    public Set<Enseignant> getEnseignants(Session session) {
        List<Object[]> querry = session.createQuery("from Etudiant as e join e.inscriptions as i join i.cours as c where e.id = " + this.id).list();

        ArrayList<Cours> coursRecu = new ArrayList<Cours>();

        for (Object[] o : querry) {
            coursRecu.add((Cours)o[2]);
        }

        listeEnseignants.clear();
        for (Cours c : coursRecu){
            if(!listeEnseignants.contains(c.getEnseignant())) {
                listeEnseignants.add(c.getEnseignant());
            }
        }
        return listeEnseignants;
    }
}
